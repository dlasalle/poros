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


struct refinement_info_struct {
  sl::FixedPriorityQueue<wgt_diff_type, vtx_type> pqs[NUM_BISECTION_PARTS];
  PartitioningAnalyzer analyzer;
  sl::BitArray visited;
};

void performIter(
    ConstantGraph const * const graph,
    Partitioning * const partitioning,
    TwoWayConnectivity * const connectivity,
    refinement_info_struct * const info)
{
  // fill priority queue with boundary vertices
  for (pid_type side = 0; side < NUM_BISECTION_PARTS; ++side) {
    vtx_type const numVertices = connectivity->getNumBorderVertices(side);
    for (vtx_type v = 0; v < numVertices; ++v) {
      info->pqs[side].add(-connectivity->getVertexDelta(v), v);
    }
  }

  // empty priority queues
  while (info->pqs[0].size() > 0 || info->pqs[1].size() > 0) {

    pid_type from;
    // decide our direction of movement
    if (info->analyzer.isOverWeight(0)) {
      // fix balance by moving vertices out of 0
      from = 0;
    } else if (info->analyzer.isOverWeight(1)) {
      // fix balance by moving vertices out of 1
      from = 1;
    } else {
      // if a priority queue is empty choose the other one
      if (info->pqs[0].size() == 0) {
        from = 1;
      } else if (info->pqs[1].size() == 0) {
        from = 0;
      } else { 
        // move from highest priority pq
        if (info->pqs[0].max() > info->pqs[1].max()) {
          from = 0;
        } else if (info->pqs[0].max() > info->pqs[1].max()) {
          from = 1;
        } else {
          // break the tie via a random number
          from = sl::Random::inRange(0,1);
        }
      }
    }
    pid_type const to = from ^ 0x01;

    wgt_diff_type const gain = info->pqs[from].max(); 
    vtx_type const vertex = info->pqs[from].pop();

    moveVertex();

  }
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
  refinement_info_struct info{
    { {0, graph->getNumVertices()}, {0, graph->getNumVertices()} },
    {partitioning, target},
    {graph->getNumVertices()}
  };

  int const maxRefIters = params->getMaxRefinementIterations();
  for (int refIter = 0; refIter < maxRefIters; ++refIter) {
     
    performIter(graph, partitioning, connectivity, &info);

    if (refIter+1 < maxRefIters) {
      // we'll do another loop
      visited.clear();
    }
  }
   
}


}

