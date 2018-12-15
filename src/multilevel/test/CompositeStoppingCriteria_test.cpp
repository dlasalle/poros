/**
* @file CompositeStoppingCriteria_test.cpp
* @brief Unit tests for the CompositeStoppingCriteria class.
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

#include "multilevel/CompositeStoppingCriteria.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"

namespace poros
{


/******************************************************************************
* MOCK CLASSES ****************************************************************
******************************************************************************/

namespace
{

class FalseStoppingCriteria : public IStoppingCriteria
{
  bool shouldStop(
      int,
      Graph const *,
      Graph const *) const override
  {
    return false;
  }
};

class TrueStoppingCriteria : public IStoppingCriteria
{
  bool shouldStop(
      int,
      Graph const *,
      Graph const *) const override
  {
    return true;
  }
};

}


/******************************************************************************
* UNIT TESTS ******************************************************************
******************************************************************************/

UNITTEST(CompositeStoppingCriteria, Empty)
{
  // graph with 144 edges
  GridGraphGenerator genFine(4, 4, 4);
  Graph fine = genFine.generate();

  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  Graph coarse = genCoarse.generate();
  
  CompositeStoppingCriteria criteria;

  testFalse(criteria.shouldStop(1, &fine, &coarse));
  testFalse(criteria.shouldStop(1, &fine, &fine));
  testFalse(criteria.shouldStop(0, nullptr, &fine));
}

UNITTEST(CompositeStoppingCriteria, ShouldContinue)
{
  // graph with 144 edges
  GridGraphGenerator genFine(4, 4, 4);
  Graph fine = genFine.generate();

  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  Graph coarse = genCoarse.generate();
  
  CompositeStoppingCriteria criteria;

  criteria.add(
    std::unique_ptr<IStoppingCriteria>(new FalseStoppingCriteria));
  criteria.add(
    std::unique_ptr<IStoppingCriteria>(new FalseStoppingCriteria));

  testFalse(criteria.shouldStop(1, &fine, &coarse));
}


UNITTEST(CompositeStoppingCriteria, ShouldStop)
{
  // graph with 144 edges
  GridGraphGenerator genFine(4, 4, 4);
  Graph fine = genFine.generate();

  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  Graph coarse = genCoarse.generate();

  CompositeStoppingCriteria criteria;

  criteria.add(
    std::unique_ptr<IStoppingCriteria>(new FalseStoppingCriteria));
  criteria.add(
    std::unique_ptr<IStoppingCriteria>(new TrueStoppingCriteria));

  testTrue(criteria.shouldStop(1, &fine, &coarse));
}

}
