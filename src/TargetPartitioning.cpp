/**
* @file TargetPartitioning.cpp
* @brief Implementation of the TargetPartitioning class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-24
*/



#include "TargetPartitioning.hpp"
#include "Debug.hpp"


namespace dolos
{


/******************************************************************************
* CONSTANTS *******************************************************************
******************************************************************************/


namespace
{

double const FRACTION_SUM_TOLERANCE = 0.0001;
double const MIN_FRACTION_SUM = 1.0 - FRACTION_SUM_TOLERANCE;
double const MAX_FRACTION_SUM = 1.0 + FRACTION_SUM_TOLERANCE;

}


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/


void calcTargetWeight(
    pid_type const numPartitions,
    wgt_type const totalVertexWeight,
    double const * const fractions,
    wgt_type * const targetWeight) noexcept
{
  wgt_type assignedWeight = 0;
  for (pid_type part = 0; part < numPartitions; ++part) {
    targetWeight[part] = fractions[part] * totalVertexWeight;
    assignedWeight += targetWeight[part];
  }

  wgt_type excessWeight = totalVertexWeight - assignedWeight; 
  if (excessWeight >= numPartitions) {
    wgt_type const base = excessWeight / numPartitions;
    for (pid_type part = 0; part < numPartitions; ++part) {
      targetWeight[part] += base;
    }
    excessWeight -= base * numPartitions;
  }
  ASSERT_LESS(excessWeight, numPartitions);

  // place any excess weight
  for (pid_type part = 0; part < excessWeight; ++part) {
    targetWeight[part] += 1; 
  }
}


void calcMaxWeight(
    pid_type const numPartitions,
    double const imbalanceTolerance,
    wgt_type const * const targetWeight,
    wgt_type * const maxWeight) noexcept
{
  for (pid_type part = 0; part < numPartitions; ++part) {
    maxWeight[part] = targetWeight[part] * imbalanceTolerance;
  }
}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


TargetPartitioning::TargetPartitioning(
    pid_type const numPartitions,
    wgt_type const totalVertexWeight,
    double const imbalanceTolerance) :
  m_numPartitions(numPartitions),
  m_totalVertexWeight(totalVertexWeight),
  m_imbalanceTolerance(imbalanceTolerance),
  m_fractions(1.0 / numPartitions, numPartitions),
  m_targetWeight(numPartitions),
  m_maxWeight(numPartitions)
{
  calcTargetWeight(numPartitions, totalVertexWeight, m_fractions.data(), \
      m_targetWeight.data());
  calcMaxWeight(numPartitions, imbalanceTolerance, \
      m_targetWeight.data(), m_maxWeight.data());
}


TargetPartitioning::TargetPartitioning(
    pid_type const numPartitions,
    wgt_type const totalVertexWeight,
    double const imbalanceTolerance,
    double const * const fractions) :
  m_numPartitions(numPartitions),
  m_totalVertexWeight(totalVertexWeight),
  m_imbalanceTolerance(imbalanceTolerance),
  m_fractions(fractions, numPartitions),
  m_targetWeight(numPartitions),
  m_maxWeight(numPartitions)
{
  double fractionSum = 0;
  for (size_t i = 0; i < m_numPartitions; ++i) {
    if (m_fractions[i] < 0.0 || m_fractions[i] > 1.0) {
      throw InvalidPartitionFractionsException(std::string("Invalid target " \
          "fractions {") + std::to_string(m_fractions[0]) + \
          std::string(", ") + std::to_string(m_fractions[1]) + \
          std::string("} . Must be between 0.0 and 1.0."));
    }
    fractionSum += m_fractions[i];
  }
  if (fractionSum < MIN_FRACTION_SUM || fractionSum > MAX_FRACTION_SUM) {
    throw InvalidPartitionFractionsException(std::string("Invalid target " \
        "fractions {") + std::to_string(m_fractions[0]) + std::string(", ") + \
        std::to_string(m_fractions[1]) + std::string("} . Must sum to 1.0."));
  }

  calcTargetWeight(numPartitions, totalVertexWeight, m_fractions.data(), \
      m_targetWeight.data());
  calcMaxWeight(numPartitions, imbalanceTolerance, m_targetWeight.data(), \
      m_maxWeight.data());
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


wgt_type const * TargetPartitioning::getMaxWeight() const
{
  return m_maxWeight.data();
}


}
