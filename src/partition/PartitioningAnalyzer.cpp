/**
* @file PartitioningAnalyzer.cpp
* @brief Implementation of the PartitioningAnalyzer class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-31
*/



#include "PartitioningAnalyzer.hpp"



namespace dolos
{


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
  double max = 0.0;
  pid_type const numPartitions = m_partitioning->numPartitions();

  for (pid_type part = 0; part < numPartitions; ++part) {
    double const frac = getImbalance(part);
    if (frac > max) {
      max = frac;
    }
  }

  return max;
}




}
