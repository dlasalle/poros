/**
* @file RandomFMBisector.cpp
* @brief Implementation of the RandomFMBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-11-06
*/


#include "RandomFMBisector.hpp"


namespace dolos
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

RandomFMBisector::RandomFMBisector(
    int maxIters) :
  m_bisector(),
  m_refiner(maxIters)
{
  // do nothing
}


RandomFMBisector::~RandomFMBisector()
{
  // do nothing
}


/******************************************************************************
* PUBLIC FUNCTIONS ************************************************************
******************************************************************************/

Partitioning RandomFMBisector::execute(
    TargetPartitioning const * const target,
    ConstantGraph const * const graph) const
{
  Partitioning part = m_bisector.execute(target, graph);

  TwoWayConnectivity conn(graph, &part);

  m_refiner.refine(target, &conn, &part, graph);

  return part;
}


}