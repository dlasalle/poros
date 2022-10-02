/**
* @file TargetPartitioning.cpp
* @brief Implementation of the TargetPartitioning class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-24
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/



#include "TargetPartitioning.hpp"

#include "solidutils/Debug.hpp"

#include <string>


namespace poros
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

namespace
{

void calcTargetWeight(
    pid_type const numPartitions,
    wgt_type const totalVertexWeight,
    double const * const fractions,
    wgt_type * const targetWeight) noexcept
{
  wgt_type assignedWeight = 0;
  for (pid_type part = 0; part < numPartitions; ++part) {
    targetWeight[part] = \
        static_cast<wgt_type>(fractions[part] * totalVertexWeight);
    assignedWeight += targetWeight[part];
  }

  // NOTE: total assignedWeight may be less than total vertex weight
}


void calcMaxWeight(
    pid_type const numPartitions,
    wgt_type const totalVertexWeight,
    double const imbalanceTolerance,
    double const * const fractions,
    wgt_type * const maxWeight) noexcept
{
  for (pid_type part = 0; part < numPartitions; ++part) {
    maxWeight[part] = \
        static_cast<wgt_type>(fractions[part] * (1.0+imbalanceTolerance) * totalVertexWeight);
  }
}

void calcFractions(
    pid_type const numPartitions,
    wgt_type const * const targetWeight,
    double * const fractions) noexcept
{
  wgt_type total = 0;
  for (pid_type part = 0; part < numPartitions; ++part) {
    total += targetWeight[part];
  }

  const double invTotal = 1.0 / static_cast<double>(total);
  for (pid_type part = 0; part < numPartitions; ++part) {
    fractions[part] = static_cast<double>(targetWeight[part])*invTotal;
  }
}



}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


TargetPartitioning::TargetPartitioning(
    pid_type const numPartitions,
    wgt_type const totalVertexWeight,
    double const imbalanceTolerance) :
  TargetPartitioning(numPartitions, totalVertexWeight, imbalanceTolerance,
      sl::Array<double>(numPartitions, 1.0 / numPartitions).data())
{
  // do nothing
}


TargetPartitioning::TargetPartitioning(
    pid_type const numPartitions,
    wgt_type const totalVertexWeight,
    double const imbalanceTolerance,
    double const * const fractions) :
  m_numPartitions(numPartitions),
  m_targetFraction(numPartitions),
  m_targetWeight(numPartitions),
  m_maxWeight(numPartitions)
{
  std::copy(fractions, fractions+numPartitions, m_targetFraction.begin());

  double fractionSum = 0;
  for (pid_type i = 0; i < m_numPartitions; ++i) {
    if (m_targetFraction[i] < 0.0 || m_targetFraction[i] > 1.0) {
      throw InvalidPartitionFractionsException(std::string("Invalid target " \
          "fractions {") + std::to_string(m_targetFraction[0]) + \
          std::string(", ") + std::to_string(m_targetFraction[1]) + \
          std::string("} . Must be between 0.0 and 1.0."));
    }
    fractionSum += m_targetFraction[i];
  }
  if (fractionSum < MIN_FRACTION_SUM || fractionSum > MAX_FRACTION_SUM) {
    throw InvalidPartitionFractionsException(std::string("Invalid target " \
        "fractions {") + std::to_string(m_targetFraction[0]) + \
        std::string(", ") + std::to_string(m_targetFraction[1]) + \
        std::string("} . Must sum to 1.0."));
  }

  calcTargetWeight(numPartitions, totalVertexWeight, m_targetFraction.data(), \
      m_targetWeight.data());
  calcMaxWeight(numPartitions, totalVertexWeight, imbalanceTolerance,
      m_targetFraction.data(), m_maxWeight.data());
}


TargetPartitioning::TargetPartitioning(
    pid_type const numPartitions,
    sl::Array<wgt_type> targetWeights,
    sl::Array<wgt_type> maxWeights) :
  m_numPartitions(numPartitions),
  m_targetFraction(numPartitions),
  m_targetWeight(std::move(targetWeights)),
  m_maxWeight(std::move(maxWeights))
{
  calcFractions(numPartitions, m_targetWeight.data(), m_targetFraction.data());
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


wgt_type const * TargetPartitioning::getMaxWeight() const
{
  return m_maxWeight.data();
}


wgt_type const * TargetPartitioning::getTargetWeight() const
{
  return m_targetWeight.data();
}


double const * TargetPartitioning::getTargetFraction() const
{
  return m_targetFraction.data();
}


}
