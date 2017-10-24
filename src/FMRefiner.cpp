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

namespace dolos
{



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
    TwoWayConnectivity * const connectivity,
    Partitioning * const partitioning,
    ConstantGraph const * const graph) const
{
  BitArray visited(graph->getNumVertices());

  FixedPriorityQueue<wgt_diff_type, vtx_type> pqs[NUM_BISECTION_PARTS] = {
      {0, graph->getNumVertices()},
      {0, graph->getNumVertices()}
  };



  int const maxRefIters = params->getMaxRefinementIterations();
  for (int refIter = 0; refIter < maxRefIters; ++refIter) {
    // fill priority queue with boundary vertices
    for (pid_type side = 0; side < NUM_BISECTION_PARTS; ++side) {
      vtx_type const numVertices = connectivity->getNumBorderVertices(side);
      for (vtx_type v = 0; v < numVertices; ++v) {
        pqs[side].add(-connectivity->getVertexDelta(v), v);
      }
    }

    if (refIter+1 < maxRefIters) {
      pid_type from;
      // decide our direction of movement
      if (partitioning->isOverWeight(0)) {
        // fix balance by moving vertices out of 0
        from = 0;
      } else if (partitioning->isOverWeight(1)) {
        // fix balance by moving vertices out of 1
        from = 1;
      } else {
        // move from highest priority pq
        if (pqs[0].max() > pqs[1].max()) {
          from = 0;
        } else if (pqs[0].max() > pqs[1].max()) {
          from = 1;
        } else {
          // vertices have same priority -- see which move will make us more
          // balanced

          wgt_type const topLeftWeight = graph->getVertexWeight(pqs[0].peek());
          wgt_type const topRightWeight = graph->getVertexWeight( \
              pqs[1].peek());

          double const leftToRightBalance = \
              (partitioning->getWeight(0) + topLeftWeight)


          if ( ) {
          } else if ( ) {
          } else {
            // break the tie via a random number
            from = Random::inRange(0,1);
          }
        }
      }
      pid_type const to = (from + 1) % 2;

      // we'll do another loop
      visited.clear();
    }
  }
   
}


}

