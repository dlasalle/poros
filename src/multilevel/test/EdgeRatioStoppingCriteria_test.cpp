/**
* @file EdgeRatioStoppingCriteria_test.cpp
* @brief Unit tests for the EdgeRatioStoppingCriteria class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-21
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

#include "multilevel/EdgeRatioStoppingCriteria.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"

namespace poros
{

UNITTEST(EdgeRatioStoppingCriteria, ShouldContinue)
{
  // graph with 144 edges
  GridGraphGenerator genFine(4, 4, 4);
  Graph fine = genFine.generate();

  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  Graph coarse = genCoarse.generate();
  
  EdgeRatioStoppingCriteria criteria(0.8);

  testFalse(criteria.shouldStop(1, &fine, &coarse));
}

UNITTEST(EdgeRatioStoppingCriteria, ShouldStop)
{
  // graph with 144 edges
  GridGraphGenerator genFine(4, 4, 4);
  Graph fine = genFine.generate();

  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  Graph coarse = genCoarse.generate();
  
  EdgeRatioStoppingCriteria criteria(0.5);

  testTrue(criteria.shouldStop(1, &fine, &coarse));
}


UNITTEST(EdgeRatioStoppingCriteria, ZeroFine)
{
  // graph with 144 edges
  GridGraphGenerator genFine(1, 1, 1);
  Graph fine = genFine.generate();

  // graph with 108 edges
  GridGraphGenerator genCoarse(1, 1, 1);
  Graph coarse = genCoarse.generate();
  
  EdgeRatioStoppingCriteria criteria(0.75);

  testTrue(criteria.shouldStop(1, &fine, &coarse));
}

UNITTEST(EdgeRatioStoppingCriteria, NullFineContinue)
{
  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  Graph coarse = genCoarse.generate();
  
  EdgeRatioStoppingCriteria criteria(0.75);

  testFalse(criteria.shouldStop(0, nullptr, &coarse));
}

UNITTEST(EdgeRatioStoppingCriteria, NullFineStop)
{
  // graph with 108 edges
  GridGraphGenerator genCoarse(1, 1, 1);
  Graph coarse = genCoarse.generate();
  
  EdgeRatioStoppingCriteria criteria(0.75);

  testTrue(criteria.shouldStop(0, nullptr, &coarse));
}

}
