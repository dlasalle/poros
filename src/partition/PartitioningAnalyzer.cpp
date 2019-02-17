/**
* @file PartitioningAnalyzer.cpp
* @brief Implementation of the PartitioningAnalyzer class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-31
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



#include "PartitioningAnalyzer.hpp"

#include <utility>


namespace poros
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{

std::pair<pid_type, double> findMax(
    PartitioningAnalyzer const * const analyzer,
    pid_type const numPartitions)
{
  double max = 0.0;
  pid_type maxId = 0;

  for (pid_type part = 0; part < numPartitions; ++part) {
    double const frac = analyzer->getImbalance(part);
    if (frac > max) {
      max = frac;
      maxId = part;
    }
  }

  return std::make_pair(maxId, max);
}

}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

PartitioningAnalyzer::PartitioningAnalyzer(
    Partitioning const * part,
    TargetPartitioning const * target) :
  m_partitioning(part),
  m_target(target)
{
  // do nothing
}

/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

double PartitioningAnalyzer::calcMaxImbalance() const
{
  return findMax(this, m_partitioning->numPartitions()).second;
}


pid_type PartitioningAnalyzer::findMostOverWeightPartition() const
{
  return findMax(this, m_partitioning->numPartitions()).first;
}




}
