/**
* @file BisectionPartitioner.cpp
* @brief Implementation of the BisectionPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-11-08
*/


#include "BisectionPartitioner.hpp"
#include "solidutils/Exception.hpp"


namespace dolos
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


BisectionPartitioner::BisectionPartitioner(
    IPartitioner const * const partitioner) :
  m_partitioner(partitioner)
{
  // do nothing
}


BisectionPartitioner::~BisectionPartitioner()
{
  // do nothing
}


/******************************************************************************
* PUBLIC FUNCTIONS ************************************************************
******************************************************************************/


Partitioning BisectionPartitioner::execute(
    TargetPartitioning const * target,
    ConstantGraph const * graph) const
{
  if (target->getNumPartitions() != 2) {
    throw sl::InvalidInputException( \
        std::string("Number of partitions must be 2: got ") +
        std::to_string(target->getNumPartitions()));
  }

  return m_partitioner->execute(target, graph);
}


}