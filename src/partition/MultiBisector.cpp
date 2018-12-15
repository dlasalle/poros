/**
* @file MultiBisector.cpp
* @brief THe MultiBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-20
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


#include "MultiBisector.hpp"
#include "partition/PartitioningAnalyzer.hpp"


namespace poros
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
    Graph const * const graph)
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
