/**
* @file FMRefiner.cpp
* @brief Implementation of the FM refiner.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-19
*/



#include "FMRefiner.hpp"
#include "BitArray.hpp" 


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

  int const maxRefIters = params->getMaxRefinementIterations();
  for (int refIter = 0; refIter < maxRefIters; ++refIter) {
    // fill priority queue with boundary vertices
    

    if (refIter+1 < maxRefIters) {
      // we'll do another loop
      visited.clear();
    }
  }
   
}


}

