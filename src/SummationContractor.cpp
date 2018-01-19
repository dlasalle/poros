/**
* @file SummationContractor.cpp
* @brief Implementation of the SummationContractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-01-17
*/




#include "SummationContractor.hpp"
#include "TwoStepGraphBuilder.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


SummationContractor::SummationContractor()
{
  // do nothing
}




/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


ConstantGraph SummationContractor::contract(
    ConstantGraph const * const graph,
    Aggregation const * const aggregation)
{
  OneStepGraphBuilder builder;

  // reserve space in our buffers
  std::vector<vtx_type> neighbors;
  neighbors.reserve(aggregation.getNumCoarseVertices());
  std::vector<wgt_type> edgeWeights;
  edgeWeights.reserve(aggregation.getNumCoarseVertices());

  // go over each fine vertex
  for (VertexGroup const & group : aggregation->getCoarseVertices()) {
    for (vtx_type const fine : group.fineVertices()) {
      
    }
  }


  return builder.finish();
}




}
