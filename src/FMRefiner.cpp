/**
* @file FMRefiner.cpp
* @brief Implementation of the FM refiner.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-19
*/



#include <vector>
#include "FMRefiner.hpp"
#include "PartitioningAnalyzer.hpp"
#include "solidutils/Debug.hpp"
#include "solidutils/Random.hpp"
#include "solidutils/BitArray.hpp" 
#include "solidutils/FixedPriorityQueue.hpp"

namespace dolos
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{


/**
* @brief Alias our VertexQueue to be a FixedPriorityQueue.
*/
typedef sl::FixedPriorityQueue<wgt_diff_type, vtx_type> VertexQueue;


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
    VertexQueue const * const pqs)
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
      } else if (pqs[0].max() > pqs[1].max()) {
        from = 1;
      } else {
        // break the tie via a random number
        from = sl::Random::inRange(0,2);
      }
    }
  }

  return from;
}


void move(
    vtx_type const vertex,
    pid_type const to,
    ConstantGraph const * const graph,
    Partitioning * const partitioning,
    TwoWayConnectivity * const connectivity,
    VertexQueue * const pqs,
    sl::BitArray * const visited)
{
  ASSERT_NOTEQUAL(to, partitioning->getAssignment(vertex));

  wgt_diff_type const delta = connectivity->getVertexDelta(vertex);

  // update connectivity
  connectivity->move(vertex);
  for (Edge const & edge : graph->getEdges(vertex)) {
    vtx_type const u = edge.getVertex();
    pid_type const neighborHome = partitioning->getAssignment(u);
    int const borderStatus = connectivity->updateNeighbor(&edge, \
        TwoWayConnectivity::getDirection(to, neighborHome));

    if (pqs && !visited->check(vertex)) {
      if (borderStatus == TwoWayConnectivity::BORDER_ADDED) {
          // insert into priority queue
          // TODO: repeating this add '-' getVertexDelta() in two places seems
          // prone to error -- combine in the future.
          pqs[neighborHome].add(-connectivity->getVertexDelta(u), u);
      } else if (borderStatus == TwoWayConnectivity::BORDER_REMOVED) {
        vtx_type const u = edge.getVertex();
        // insert into priority queue
        pqs[neighborHome].remove(u);
      }
    }
  }

  // update partitioning
  partitioning->move(vertex, to);
  partitioning->addCutEdgeWeight(delta);
}


}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


FMRefiner::FMRefiner(
    int const maxRefIters) :
  m_maxRefinementIters(maxRefIters)
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
    ConstantGraph const * const graph) const
{
  VertexQueue pqs[]{ \
    {graph->getNumVertices()}, \
    {graph->getNumVertices()} \
  };
  PartitioningAnalyzer analyzer(partitioning, target);
  sl::BitArray visited(graph->getNumVertices());

  double const tolerance = target->getImbalanceTolerance();

  std::vector<vtx_type> moves;
  moves.reserve(graph->getNumVertices());

  for (int refIter = 0; refIter < m_maxRefinementIters; ++refIter) {
    
    // delete me
    DEBUG_MESSAGE(std::string("Cut is ") + \
        std::to_string(partitioning->getCutEdgeWeight()) + \
        std::string(" with balance of ") + \
        std::to_string(analyzer.calcMaxImbalance()) + \
        std::string("/") + std::to_string(target->getImbalanceTolerance()) + \
        std::string(" at iter ") + std::to_string(refIter));
     
    // fill priority queue with boundary vertices
    for (vtx_type const vertex : *(connectivity->getBorderVertexSet())) {
      pid_type const side = partitioning->getAssignment(vertex);
      pqs[side].add(-connectivity->getVertexDelta(vertex), vertex);
    }

    moves.clear();
    wgt_type bestCut = partitioning->getCutEdgeWeight();
    double bestBalance = analyzer.calcMaxImbalance();

    vtx_type numMoved = 0;

    // move all possible vertices
    while (pqs[0].size() > 0 || pqs[1].size() > 0) {
      pid_type const from = pickSide(&analyzer, pqs); 
      pid_type const to = from ^ 1;

      vtx_type const vertex = pqs[from].pop();
      visited.mark(vertex);
      ASSERT_EQUAL(from, partitioning->getAssignment(vertex));

      move(vertex, to, graph, partitioning, connectivity, pqs, &visited);

      wgt_type const currentCut = partitioning->getCutEdgeWeight();
      double const balance = analyzer.calcMaxImbalance();

      if (bestBalance > tolerance && balance < bestBalance) {
        bestCut = currentCut;
        bestBalance = balance;
        moves.clear();
      } else if (currentCut < bestCut && (balance < tolerance || \
          balance < bestBalance)) {
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
    ASSERT_TRUE(connectivity->verify(partitioning));

    // undo bad moves
    for (size_t i = moves.size(); i > 0;) {
      --i;

      vtx_type const vertex = moves[i];
      pid_type const from = partitioning->getAssignment(vertex);
      pid_type const to = from ^ 1;

      move(vertex, to, graph, partitioning, connectivity, nullptr, nullptr);
    }
    ASSERT_TRUE(connectivity->verify(partitioning));
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

