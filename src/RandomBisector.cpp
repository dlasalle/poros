/**
 * @file RandomBisector.cpp
 * @brief Implementation of RandomParittioner. 
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#include "RandomBisector.hpp"
#include "RandomTraverser.hpp"


namespace dolos
{


namespace
{

double const FRACTION_SUM_TOLERANCE = 0.0001;

}


/******************************************************************************
* CONSTRUCTORS ****************************************************************
******************************************************************************/

RandomBisector::RandomBisector(
    BisectionParameters const * params) :
  m_params(*params)
{
  // do nothing
}

RandomBisector::~RandomBisector()
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Partitioning RandomBisector::execute(
    ConstantGraph const * const graph) const
{
  wgt_type const totalWeight = graph->getTotalVertexWeight();

  // construct maximum partition weights
  wgt_type maxPartitionWeight[NUM_BISECTION_PARTS];
  maxPartitionWeight[LEFT_PARTITION] = totalWeight * \
      m_params.getLeftSideMax();
  maxPartitionWeight[RIGHT_PARTITION] = \
      totalWeight * m_params.getRightSideMax(); 

  // random vertex order
  RandomTraverser traverser(graph->getNumVertices());

  wgt_type const * const vertexWeight = graph->getVertexWeight();

  // start with all vertices in the right partition
  Partitioning partitioning(NUM_BISECTION_PARTS, graph->getNumVertices());
  partitioning.assignAll(RIGHT_PARTITION, graph->getTotalVertexWeight());

  while (traverser.next()) {
    vtx_type const vtx = traverser.get();
    if (partitioning.getWeight(LEFT_PARTITION) + vertexWeight[vtx] <= \
        maxPartitionWeight[LEFT_PARTITION]) {
      partitioning.move(vtx, vertexWeight[vtx], LEFT_PARTITION);
    }
  }

  // by construction the left partition cannot be overweight at this point
  if (partitioning.getWeight(RIGHT_PARTITION) > \
      maxPartitionWeight[RIGHT_PARTITION]) {
    // TODO: rebalance as neccessary
  }

  return partitioning;
}


}
