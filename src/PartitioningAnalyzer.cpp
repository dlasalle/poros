/**
* @file PartitioningAnalyzer.cpp
* @brief The PartitioningAnalyzer class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/



#include "PartitioningAnalyzer.hpp"


namespace dolos
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

PartitioningAnalyzer::PartitioningAnalyzer(
    ConstantGraph const * graph,
    Partitioning const * partitioning) :
  m_graph(graph),
  m_partitioning(partitioning)
{
  // do nothing -- all calculations are lazy, to allow this class to used
  // wherever needed without penalty
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


double PartitioningAnalyzer::calcMaxImbalance(
  double const * const targetFractions) const
{
  pid_type const numParts = m_partitioning->getNumPartitions();  

  wgt_type const totalWeight = m_graph->getTotalVertexWeight();

  double max = 0.0;

  for (pid_type part = 0; part < numParts; ++part) {
    double const fraction = \
        static_cast<double>(m_partitioning->getWeight(part)) / \
        static_cast<double>(totalWeight);
    double const imbalance = (fraction / targetFractions[part]) - 1.0;

    if (imbalance > max) {
      max = imbalance; 
    }
  }

  return max;
}




}
