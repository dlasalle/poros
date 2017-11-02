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
  pid_type from;
  // decide our direction of movement
  if (analyzer->isOverWeight(0)) {
    // fix balance by moving vertices out of 0
    from = 0;
  } else if (analyzer->isOverWeight(1)) {
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
        from = sl::Random::inRange(0,1);
      }
    }
  }

  return from;
}


}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


FMRefiner::FMRefiner()
{

}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


void FMRefiner::refine(
    BisectionParameters const * const params,
    TargetPartitioning const * const target,
    TwoWayConnectivity * const connectivity,
    Partitioning * const partitioning,
    ConstantGraph const * const graph) const
{
  VertexQueue pqs[]{ \
    {0, graph->getNumVertices()}, \
    {0, graph->getNumVertices()} \
  };
  PartitioningAnalyzer analyzer(partitioning, target);
  sl::BitArray visited(graph->getNumVertices());

  std::vector<vtx_type> moves;
  moves.reserve(graph->getNumVertices());

  int const maxRefIters = params->getMaxRefinementIterations();
  for (int refIter = 0; refIter < maxRefIters; ++refIter) {
     
    // fill priority queue with boundary vertices
    for (vtx_type const vertex : *(connectivity->getBorderVertexSet())) {
      pid_type const side = partitioning->getAssignment(vertex);
      pqs[side].add(-connectivity->getVertexDelta(vertex), vertex);
    }

    moves.clear();
    wgt_type bestCut = partitioning->getCutEdgeWeight();

    // move all possible vertices
    while (pqs[0].size() > 0 || pqs[1].size() > 0) {
      pid_type const from = pickSide(&analyzer, pqs); 
      pid_type const to = from ^ 1;

      vtx_type const vertex = pqs[from].pop();
      wgt_diff_type const delta = connectivity->getVertexDelta(vertex);

      // update connectivity
      connectivity->move(vertex);
      for (Edge const & edge : graph->getEdges(vertex)) {
        bool const addedToBorder = connectivity->updateNeighbor(&edge, to);
        if (addedToBorder && !visited.check(vertex)) {
          vtx_type const u = edge.getVertex();
          pid_type const other = partitioning->getAssignment(u);
          // insert into priority queue
          // TODO: repeating this add '-' getVertexDelta() in two places seems prone
          // to error -- combine in the future.
          pqs[other].add(-connectivity->getVertexDelta(u), u);
        }
      }

      // update partitioning
      partitioning->move(vertex, to);
      partitioning->addCutEdgeWeight(delta);

      wgt_type const currentCut = partitioning->getCutEdgeWeight();
      if (currentCut < bestCut) {
        bestCut = currentCut;
        moves.clear();
      } else {
        moves.emplace_back(vertex); 
      }

      visited.mark(vertex);
    }

    // undo bad moves
    for (size_t i = moves.size(); i > 0;) {
      --i;

      vtx_type const vertex = moves[i];

      connectivity->move(vertex);
    }


    // empty priority queues
    if (refIter+1 < maxRefIters) {
      // we'll do another loop
      visited.clear();
    }
  }
   
}


}

