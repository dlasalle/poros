/**
* @file BisectionPartitioner.cpp
* @brief Implementation of the BisectionPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-11-08
*/


#include "BisectionPartitioner.hpp"


namespace dolos
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


BisectionPartitioner::BisectionPartitioner(
    IPartitioner * const partitioner) :
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
    TargetPartitioning const * const target,
    ConstantGraph const * const graph)
{
  if (target->numPartitions() != 2) {
    throw std::runtime_error( \
        std::string("Number of partitions must be 2: got ") +
        std::to_string(target->numPartitions()));
  }

  return m_partitioner->execute(target, graph);
}


}
