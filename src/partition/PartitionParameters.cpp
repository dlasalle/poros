/**
* @file PartitionParameters.cpp
* @brief Implementation of the PartitionParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-11
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


#include "PartitionParameters.hpp"




namespace poros
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
