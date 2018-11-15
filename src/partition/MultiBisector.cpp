/**
* @file MultiBisector.cpp
* @brief THe MultiBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-20
*/


#include "MultiBisector.hpp"
#include "partition/PartitioningAnalyzer.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

MultiBisector::MultiBisector(
    int numBisections,
    std::unique_ptr<IBisector> bisector) :
  m_numBisections(numBisections),
  m_bisector(std::move(bisector))
{
  if (m_bisector.get() == nullptr) {
    throw std::runtime_error("Bisector cannot but null.");
  }
}


MultiBisector::~MultiBisector()
{
  // do nothing
}




/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Partitioning MultiBisector::execute(
    TargetPartitioning const * const target,
    ConstantGraph const * const graph)
{
  wgt_type bestBisection = 0;
  double bestBalance = 0.0;
  bool balancedFound = false;

  Partitioning bestPart(2, graph);

  for (int b = 0; b < m_numBisections; ++b) {
    Partitioning part = m_bisector->execute(target, graph);

    PartitioningAnalyzer analyzer(&part, target);

    double const balance = analyzer.calcMaxImbalance();

    bool const isBalanced = analyzer.isBalanced();
    bool const improvesBalance = balance < bestBalance;
    bool const improvesCut = part.getCutEdgeWeight() < bestBisection; 

    // accept the partition if it is the first, first to be properly balanced,
    // or has the best cut
    if (b == 0 || (!balancedFound && improvesBalance) || \
        (balancedFound && isBalanced && improvesCut)) {
      // save our best partition
      bestBalance = analyzer.calcMaxImbalance();
      bestBisection = part.getCutEdgeWeight();
      bestPart = std::move(part);

      if (isBalanced) {
        // note that we found a balanced bisection
        balancedFound = true;
      }
    }
  }

  return bestPart;
}


}
