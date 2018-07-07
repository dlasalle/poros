/**
* @file BFSBisector.cpp
* @brief Implementation of the BFSBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-04
*/


#include "BFSBisector.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

BFSBisector::BFSBisector(
    IRandomEngine * const rng) : m_rng(rng)
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Partitioning BFSBisector::execute(
    TargetPartitioning const * target,
    ConstantGraph const * graph) const
{
  ASSERT_EQUAL(target->numPartitions(), 2);

  Partitioning part(target->numPartitions(), graph);
    
  
}



}
