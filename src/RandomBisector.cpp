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
    Parameters const * params) :
  m_leftSideTargetFraction(0)
{
  std::vector<double> const * targetPartitionFractions = \
      params->getTargetPartitionFractions();
  pid_type const numParts = params->getNumPartitions();

  // verify that input is reasonable
  if (numParts != NUM_BISECTION_PARTS) {
    throw InvalidParametersException( \
        std::string("Invalid number of partitions for a bisection: ") + \
        std::to_string(numParts));
  }

  // sum target partition fractions and verify each one is greater than zero
  double fractionTotal = 0.0;
  for (double const frac : *targetPartitionFractions) {
    if (frac <= 0.0) {
      throw InvalidParametersException(
        std::string("Invalid target partition weight fraction: ") + \
        std::to_string(frac));
    }
    fractionTotal += frac;
  }
  if (fractionTotal <= 1.0 - FRACTION_SUM_TOLERANCE || \
      fractionTotal >= 1.0 + FRACTION_SUM_TOLERANCE) {
    throw InvalidParametersException(
        std::string("Target partition fractions do not sum to 1.0: ") + \
        std::to_string(fractionTotal));
  }

  m_leftSideTargetFraction = (*targetPartitionFractions)[LEFT_PARTITION];
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
  maxPartitionWeight[LEFT_PARTITION] = totalWeight * m_leftSideTargetFraction;
  maxPartitionWeight[RIGHT_PARTITION] = \
      totalWeight - maxPartitionWeight[LEFT_PARTITION];

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
