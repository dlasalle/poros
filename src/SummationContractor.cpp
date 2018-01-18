/**
* @file SummationContractor.cpp
* @brief Implementation of the SummationContractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-01-17
*/




#include "SummationContractor.hpp"
#include "GraphBuilder.hpp"

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


ConstantGraph SummationContract::contract(
    ConstantGraph const * const graph,
    Aggregation const * const aggregation)
{
  GraphBuilder builder;

  builder.setNumVertices(aggregation->getNumCoarseVertices());

  builder.beginVertexPhase();


  builder.beginEdgePhase();

  return builder.finish();
}




}
