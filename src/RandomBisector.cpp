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


/******************************************************************************
* CONSTRUCTORS ****************************************************************
******************************************************************************/

RandomBisector::RandomBisector()
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
    BisectionParameters const * const params,
    ConstantGraph const * const graph) const
{
  wgt_type const totalWeight = graph->getTotalVertexWeight();
  double const * const maxFractions = params->getMaxFractions();

  // construct maximum partition weights
  std::vector<wgt_type> maxPartitionWeight(NUM_BISECTION_PARTS);
  for (size_t i = 0; i < NUM_BISECTION_PARTS; ++i) {
    maxPartitionWeight[i] = totalWeight * maxFractions[i];
  }

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
