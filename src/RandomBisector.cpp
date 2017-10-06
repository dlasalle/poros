/**
 * @file RandomBisector.cpp
 * @brief Implementation of RandomParittioner. 
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#include <algorithm>
#include "IBisector.hpp"
#include "Parameters.hpp"


namespace dolos
{


namespace
{

double FRACTION_SUM_TOLERANCE = 0.001;

}


/******************************************************************************
* CONSTRUCTORS ****************************************************************
******************************************************************************/

RandomBisector::RandomBisector(
    Parameters const * params) :
  m_targetPartitionFractions(params->getTargetPartitionFractions())
{
  // verify that input is reasonable
  if (m_numParts == 2) {
    throw InvalidParametersException( \
        std::string("Invalid number of partitions for a bisection: ") + \
        std::to_string(m_numParts));
  }

  // sum target partition fractions and verify each one is greater than zero
  double fractionTotal 0.0;
  for (double const frac : m_targetPartitionFractions) {
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
        std::string(std::string("Target partition fractions do not " \
            "sum to 1.0: ") + std::to_string(fractionTotal));
  }
}

RandomBisector::~RandomBisector()
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Partitioning execute(
    Graph const * const graph) const
{
  std::vector<vtx_type> vertexPerm(graph->getNumVertices());
  std::random_shuffle(vertexPerm);

  std::vector<pid_type> partPerm(m_numParts);

  Partitioning partitioning(m_numParts, graph->getNumVertices());
  pid_type * const where = partitioning->getAssignment();

  wgt_type const * const vwgts = graph->getVertexWeights();

  std::vector<wgt_type> pwgts(m_numParts, 0);

  // go through each partition and assign a set of vertices
  vtx_type vtx = 0;
  for (pid_type part = 0; part < m_numParts; ++part) {
    pid_type const pPart = partPerm[part];
    double const targetWeight = graph->getTotalVertexWeight() * \
        m_targetPartitionFractions[pPart];
    while (partitioning.getWeight(pPart) < targetWeight) {
      vtx_type const pVtx = vertexPerm[vtx];
      partitioning.assign(pVtx, pPart);
      ++vtx;
    }
  }

  return partitioning;
}


}
