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
#include "BitArray.hpp" 
#include "FixedPriorityQueue.hpp"
#include "PartitioningAnalyzer.hpp"
#include "Random.hpp"

namespace dolos
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{

void performIter(
    ConstantGraph const * const graph,
    Partitioning * const partitioning,
    solidutils::FixedPriorityQueue<wgt_diff_type, vtx_type> * const pqs,
    PartitioningAnalyzer const * const analyzer,
    BitArray * const visited)
{
  // fill priority queue with boundary vertices
  for (pid_type side = 0; side < NUM_BISECTION_PARTS; ++side) {
    vtx_type const numVertices = connectivity->getNumBorderVertices(side);
    for (vtx_type v = 0; v < numVertices; ++v) {
      pqs[side].add(-connectivity->getVertexDelta(v), v);
    }
  }

  // empty priority queues
  while (pqs[0].size() > 0 || pqs[1].size() > 0) {

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
          from = solidutils::Random::inRange(0,1);
        }
      }
    }
    pid_type const to = from ^ 0x01;

    wgt_diff_type const gain = pqs[from].max(); 
    vtx_type const vertex = pqs[from].pop();


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
  BitArray visited(graph->getNumVertices());

  solidutils::FixedPriorityQueue<wgt_diff_type, vtx_type> \
      pqs[NUM_BISECTION_PARTS] = { \
          {0, graph->getNumVertices()}, \
          {0, graph->getNumVertices()} \
      };

  PartitioningAnalyzer analyzer(partitioning, target);

  int const maxRefIters = params->getMaxRefinementIterations();
  for (int refIter = 0; refIter < maxRefIters; ++refIter) {
     
    performIter(graph, partitioning, pqs, &analyzer, visited);

    if (refIter+1 < maxRefIters) {
      // we'll do another loop
      visited.clear();
    }
  }
   
}


}

