/**
* @file MultilevelPartitioner.cpp
* @brief Implementation of the MultilevelPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-04
*/


#include "MultilevelPartitioner.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

MultilevelPartitioner::MultilevelPartitioner(
    std::unique_ptr<IAggregator> aggregator,
    std::unique_ptr<IPartitioner> initialPartitioner,
    std::unique_ptr<IRefiner> refiner) :
  m_aggregator(std::move(aggregator)),
  m_initialPartitioner(std::move(initialPartitioner)),
  m_refiner(std::move(refiner))
{
  // do nothing 
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


Partitioning MultilevelPartitioner::execute(
    TargetPartitioning const * const target,
    ConstantGraph const * const graph)
{
  Partitioning part(target->numPartitions(), graph);

  // aggregate

  // contract

  // partition

  // project

  // refine

  return part;
}



}
