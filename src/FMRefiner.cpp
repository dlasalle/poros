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


void pickSide(
    PartitioningAnalyzer const * const analyzer,
    FixedPriorityQueue const * const pqs)
{
  pid_type from;
  // decide our direction of movement
  if (analyzer.isOverWeight(0)) {
    // fix balance by moving vertices out of 0
    from = 0;
  } else if (analyzer.isOverWeight(1)) {
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
  FixedPriorityQueue[] pqs{ \
    {0, graph->getNumVertices()}, \
    {0, graph->getNumVertices()} \
  };
  PartitioningAnalyzer analyzer(partitioning, target);
  BitArray visited(graph->getNumVertices());

  std::vector<vtx_type> moves;
  moves.reserve(graph->getNumVertices());

  int const maxRefIters = params->getMaxRefinementIterations();
  for (int refIter = 0; refIter < maxRefIters; ++refIter) {
     
    // fill priority queue with boundary vertices
    for (pid_type side = 0; side < NUM_BISECTION_PARTS; ++side) {
      vtx_type const numVertices = connectivity->getNumBorderVertices(side);
      for (vtx_type v = 0; v < numVertices; ++v) {
        pqs[side].add(-connectivity->getVertexDelta(v), v);
      }
    }

    moves.clear();
    wgt_type bestCut = partitioning->getCutEdgeWeight();

    // move all possible vertices
    while (pqs[0].size() > 0 || pqs[1].size() > 0) {
      pid_type const from = pickSide(&analyzer, pqs); 
      pid_type const to = from ^ 1;

      wgt_diff_type const gain = pqs[from].max();
      vtx_type const vertex = pqs[from].pop();

      // update connectivity
      connectivity.move(vertex);

      moves.emplace_back(vertex); 

      visited[vertex] = true;
    }

    // undo bad moves
    for (size_t i = moves.size(); i > 0;) {
      --i;

      vtx_type const vertex = moves[i];

      connectivity.move(vertex);
    }


    // empty priority queues
    if (refIter+1 < maxRefIters) {
      // we'll do another loop
      visited.clear();
    }
  }
   
}


}

