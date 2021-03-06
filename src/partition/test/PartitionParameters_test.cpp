/**
* @file PartitionParameters_test.cpp
* @brief Unit tests for the PartitionParameters class.
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


#include "partition/PartitionParameters.hpp"
#include "solidutils/UnitTest.hpp"

#include <vector>
#include <cstdlib>


namespace poros
{


UNITTEST(BisectionParameters, SetGetTolerance)
{
  PartitionParameters params(2);
  params.setImbalanceTolerance(0.015);

  testEqual(params.getImbalanceTolerance(), 0.015);
}


UNITTEST(BisectionParameters, SetGetTargetFractions)
{
  std::vector<double> targets{0.3, 0.5, 0.2};

  PartitionParameters params(targets.size());
  params.setTargetPartitionFractions(targets.data());

  double const * testTargets = params.getTargetPartitionFractions();

  for (size_t i = 0; i < targets.size(); ++i) {
    testEqual(testTargets[i], targets[i]);
  }
}


}
