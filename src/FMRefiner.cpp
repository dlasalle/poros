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
    BisectionParameters const * params,
    TwoWayConnectivity * connectivity,
    ConstantGraph const * graph) const
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
        
      }
    }

    if (refIter+1 < maxRefIters) {
      // we'll do another loop
      visited.clear();
    }
  }
   
}


}

