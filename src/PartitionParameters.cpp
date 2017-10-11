/**
* @file PartitionParameters.cpp
* @brief Implementation of the PartitionParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-11
*/


#include "PartitionParameters.hpp"




namespace dolos
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{


/**
* @brief This function is the single place max partition fractions are
* calculated.
*
* @param numPartitions The number of partitions.
* @param max The memory location to output the maximums at.
* @param target The memory location of the current target fractions.
* @param tolerance The fraction of allowable imbalance.
*/
inline void _fillMaxPartitionFractions(
    pid_type const numPartitions,
    double * const max,
    double const * const target,
    double const tolerance) noexcept
{
  for (pid_type i = 0; i < numPartitions; ++i) {
    max[i] = target[i] * (1.0 + tolerance);
  }
}


}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


PartitionParameters::PartitionParameters(
    pid_type const numPartitions) :
  m_numParts(numPartitions),
  m_imbalanceTolerance(0.03),
  m_targetPartitionFractions(numPartitions),
  m_maxPartitionFractions(numPartitions)
{
  // setup vectors
  double const target =  1.0 / static_cast<double>(numPartitions);
  for (pid_type i = 0; i < numPartitions; ++i) {
    m_targetPartitionFractions[i] = target;
  }

  _fillMaxPartitionFractions(numPartitions, m_maxPartitionFractions.data(), \
      m_targetPartitionFractions.data(), m_imbalanceTolerance);
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void PartitionParameters::setImbalanceTolerance(
    double const toleranceFraction)
{
  (void)toleranceFraction;
}


void PartitionParameters::setTargetPartitionFractions(
    double const * const fractions)
{
  (void)fractions;
}


pid_type PartitionParameters::getNumPartitions() const
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


double const * PartitionParameters::getMaxPartitionFractions() const
{
  return m_maxPartitionFractions.data();
}



}
