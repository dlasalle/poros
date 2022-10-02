/**
* @file TargetPartitioning.cpp
* @brief Unit tests for TargetPartitioning class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-11-03
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



#include "partition/TargetPartitioning.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>

namespace poros
{


UNITTEST(TargetPartitioning, GetMaxWeight)
{
  TargetPartitioning target(2, 200, 0.03); 

  testEqual(target.getMaxWeight(0), static_cast<wgt_type>(103));
  testEqual(target.getMaxWeight(1), static_cast<wgt_type>(103));

  testEqual(target.getMaxWeight()[0], static_cast<wgt_type>(103));
  testEqual(target.getMaxWeight()[1], static_cast<wgt_type>(103));
}


UNITTEST(TargetPartitioning, GetTargetWeight)
{
  TargetPartitioning target(2, 200, 0.03); 

  testEqual(target.getTargetWeight(0), static_cast<wgt_type>(100));
  testEqual(target.getTargetWeight(1), static_cast<wgt_type>(100));

  testEqual(target.getTargetWeight()[0], static_cast<wgt_type>(100));
  testEqual(target.getTargetWeight()[1], static_cast<wgt_type>(100));
}

UNITTEST(TargetPartitioning, GetMaxWeightFractions)
{
  std::vector<double> fractions{0.3, 0.3, 0.4};
  TargetPartitioning target(fractions.size(), 100, 0.05, fractions.data()); 

  testEqual(target.getMaxWeight(0), static_cast<wgt_type>(31));
  testEqual(target.getMaxWeight(1), static_cast<wgt_type>(31));
  testEqual(target.getMaxWeight(2), static_cast<wgt_type>(42));

  testEqual(target.getMaxWeight()[0], static_cast<wgt_type>(31));
  testEqual(target.getMaxWeight()[1], static_cast<wgt_type>(31));
  testEqual(target.getMaxWeight()[2], static_cast<wgt_type>(42));
}


UNITTEST(TargetPartitioning, GetTargetWeightFractions)
{
  std::vector<double> fractions{0.3, 0.3, 0.4};
  TargetPartitioning target(fractions.size(), 100, 0.05, fractions.data()); 

  testEqual(target.getTargetWeight(0), static_cast<wgt_type>(30));
  testEqual(target.getTargetWeight(1), static_cast<wgt_type>(30));
  testEqual(target.getTargetWeight(2), static_cast<wgt_type>(40));

  testEqual(target.getTargetWeight()[0], static_cast<wgt_type>(30));
  testEqual(target.getTargetWeight()[1], static_cast<wgt_type>(30));
  testEqual(target.getTargetWeight()[2], static_cast<wgt_type>(40));
}




}
