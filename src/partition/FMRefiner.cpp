/**
* @file FMRefiner.cpp
* @brief Implementation of the FM refiner.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-19
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/



#include "FMRefiner.hpp"
#include "PartitioningAnalyzer.hpp"
#include "util/VertexQueue.hpp"
#include "util/VisitTracker.hpp"

#include "solidutils/Debug.hpp"
#include "solidutils/FixedPriorityQueue.hpp"

#include <vector>
#include <array>

namespace poros
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{


/**
* @brief Choose the side to move a vertex from.
*
* @param analyzer The PartitioningAnalyzer.
* @param pqs The priority queues (must be of length 2).
*
* @return The side to move a vertex from.
*/
pid_type pickSide(
    PartitioningAnalyzer const * const analyzer,
    std::array<VertexQueue,2> const & pqs)
{
  ASSERT_GREATER(pqs[0].size() + pqs[1].size(), 0);

  pid_type from;
  // decide our direction of movement
  if (analyzer->isOverWeight(0) && pqs[0].size() > 0) {
    // fix balance by moving vertices out of 0
    from = 0;
  } else if (analyzer->isOverWeight(1) && pqs[1].size() > 0) {
    // fix balance by moving vertices out of 1
    from = 1;
  } else {
    // if a priority queue is empty choose the other one
    if (pqs[0].size() == 0) {
      from = 1;
    } else if (pqs[1].size() == 0) {
      from = 0;
    } else { 
      // move from highest priority pq
      if (pqs[0].max() > pqs[1].max()) {
        from = 0;
      } else if (pqs[0].max() < pqs[1].max()) {
        from = 1;
      } else {
        // break the tie via a pseudo-random number
        from = (pqs[0].peek().index + pqs[1].peek().index) % 2;
      }
    }
  }

  return from;
}


void move(
    Vertex const vertex,
    pid_type const to,
    Graph const * const graph,
    Partitioning * const partitioning,
    TwoWayConnectivity * const connectivity,
    VertexQueue * const pqs,
    VisitTracker * const visited)
{
  ASSERT_NOTEQUAL(to, partitioning->getAssignment(vertex));

  wgt_diff_type const delta = connectivity->getVertexDelta(vertex);

  // update connectivity
  connectivity->move(vertex);

  // update partitioning
  partitioning->move(vertex, to);
  partitioning->addCutEdgeWeight(delta);

  for (Edge const edge : graph->edgesOf(vertex)) {
    Vertex const u = graph->destinationOf(edge);
    pid_type const neighborHome = partitioning->getAssignment(u);
    int const borderStatus = connectivity->updateNeighbor(u.index, \
        graph->weightOf(edge), \
        TwoWayConnectivity::getDirection(to, neighborHome));

    if (pqs && !visited->hasVisited(u.index)) {
      if (borderStatus == TwoWayConnectivity::BORDER_ADDED) {
          // insert into priority queue
          // TODO: repeating this add '-' getVertexDelta() in two places seems
          // prone to error -- combine in the future.
          pqs[neighborHome].add(-connectivity->getVertexDelta(u), u);
      } else if (borderStatus == TwoWayConnectivity::BORDER_REMOVED) {
        Vertex const u = graph->destinationOf(edge);
        // insert into priority queue
        pqs[neighborHome].remove(u);
      } else if (borderStatus == TwoWayConnectivity::BORDER_STILLIN) {
        // update value
        pqs[neighborHome].update(-connectivity->getVertexDelta(u), u);
      }
    }
  }
}


}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

FMRefiner::FMRefiner(
    int const maxRefIters,
    vtx_type const maxMoves) :
  m_maxRefinementIters(maxRefIters),
  m_maxMoves(maxMoves)
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


void FMRefiner::refine(
    TargetPartitioning const * const target,
    TwoWayConnectivity * const connectivity,
    Partitioning * const partitioning,
    Graph const * const graph)
{
  std::array<VertexQueue, 2> pqs{{
    {graph->numVertices()}, \
    {graph->numVertices()} \
  }};
  PartitioningAnalyzer analyzer(partitioning, target);
  VisitTracker visited(graph->numVertices());

  double const tolerance = target->getImbalanceTolerance();

  std::vector<Vertex> moves;
  moves.reserve(graph->numVertices());

  vtx_type const maxNumBadMoves = std::min(m_maxMoves, \
      std::max(static_cast<vtx_type>(graph->numVertices()*0.01),
               static_cast<vtx_type>(25)));

  for (int refIter = 0; refIter < m_maxRefinementIters; ++refIter) {
    
    // delete me
    DEBUG_MESSAGE(std::string("Cut is ") + \
        std::to_string(partitioning->getCutEdgeWeight()) + \
        std::string(" with balance of ") + \
        std::to_string(analyzer.calcMaxImbalance()) + \
        std::string("/") + std::to_string(target->getImbalanceTolerance()) + \
        std::string(" at iter ") + std::to_string(refIter));

    DEBUG_MESSAGE(std::string("Number of boundary vertices is ") + \
        std::to_string(connectivity->getBorderVertexSet()->size()));
 
     
    // fill priority queue with boundary vertices
    for (vtx_type const v : *(connectivity->getBorderVertexSet())) {
      Vertex const vertex = Vertex::make(v);
      pid_type const side = partitioning->getAssignment(vertex);
      pqs[side].add(-connectivity->getVertexDelta(vertex), vertex);
    }

    moves.clear();
    wgt_type bestCut = partitioning->getCutEdgeWeight();
    double bestBalance = analyzer.calcMaxImbalance();

    vtx_type numMoved = 0;

    // move all possible vertices
    while ((pqs[0].size() > 0 || pqs[1].size() > 0) && \
        moves.size() < maxNumBadMoves) {
      pid_type const from = pickSide(&analyzer, pqs);
      pid_type const to = from ^ 1;

      ASSERT_EQUAL(pqs[from].max(), -connectivity->getVertexDelta(pqs[from].peek()));

      Vertex const vertex = pqs[from].pop();

      visited.visit(vertex.index);
      ASSERT_EQUAL(from, partitioning->getAssignment(vertex));

      move(vertex, to, graph, partitioning, connectivity, pqs.data(), &visited);

      wgt_type const currentCut = partitioning->getCutEdgeWeight();
      double const balance = analyzer.calcMaxImbalance();

      if ((bestBalance > tolerance && balance < bestBalance) ||
          (currentCut < bestCut && \
            (balance <= tolerance || balance <= bestBalance))) {
        bestCut = currentCut;
        bestBalance = balance;
        moves.clear();
      } else {
        moves.emplace_back(vertex); 
      }

      ++numMoved;
    }

    DEBUG_MESSAGE(std::string("Undoing ") + std::to_string(moves.size()) + \
        std::string("/") + std::to_string(numMoved) + std::string(" moves."));
    ASSERT_TRUE(connectivity->verify(graph, partitioning));

    // undo bad moves
    for (size_t i = moves.size(); i > 0;) {
      --i;

      Vertex const vertex = moves[i];
      pid_type const from = partitioning->getAssignment(vertex);
      pid_type const to = from ^ 1;

      move(vertex, to, graph, partitioning, connectivity, nullptr, nullptr);
    }
    ASSERT_TRUE(connectivity->verify(graph, partitioning));
    ASSERT_EQUAL(partitioning->getCutEdgeWeight(), bestCut);

    if (numMoved == moves.size()) {
      // no improvement
      DEBUG_MESSAGE("Kept zero moves, stopping refinement early.");
      break;
    }

    // empty priority queues
    if (refIter+1 < m_maxRefinementIters) {
      // we'll do another loop
      pqs[0].clear();
      pqs[1].clear();
      visited.clear();
    }
  }
   
}


}

