/**
* @file Aggregation.cpp
* @brief Implementation of the Aggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-01-15
*/


#include "Aggregation.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

Aggregation::Aggregation(
    std::vector<vtx_type> && coarseMap,
    const vtx_type numCoarseVertices) :
  m_numCoarseVertices(numCoarseVertices),
  m_coarseMap(coarseMap)
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/




}
