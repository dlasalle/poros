/**
* @file PartitionParameters.cpp
* @brief Implementation of the PartitionParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-11
*/


#include "PartitionParameters.hpp"




namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


PartitionParameters::PartitionParameters(
    pid_type const numPartitions) :
  m_numParts(numPartitions),
  m_imbalanceTolerance(0.03),
  m_targetPartitionFractions(numPartitions)
{
  // setup vectors
  double const target =  1.0 / static_cast<double>(numPartitions);
  for (pid_type i = 0; i < numPartitions; ++i) {
    m_targetPartitionFractions[i] = target;
  }
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void PartitionParameters::setImbalanceTolerance(
    double const toleranceFraction)
{
  m_imbalanceTolerance = toleranceFraction;
}


void PartitionParameters::setTargetPartitionFractions(
    double const * const fractions)
{
  for (pid_type i = 0; i < m_numParts; ++i) {
    m_targetPartitionFractions[i] = fractions[i];
  }
}


pid_type PartitionParameters::numPartitions() const
{
  return m_numParts;
}


double PartitionParameters::getImbalanceTolerance() const
{
  return m_imbalanceTolerance;
}


double const * PartitionParameters::getTargetPartitionFractions() const
{
  return m_targetPartitionFractions.data();
}


}
