/**
* @file AggregatorFactory_test.cpp
* @brief The unit test for the AggregatorFactory class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-09-06
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

#include "AggregatorFactory.hpp"
#include "RandomMatchingAggregator.hpp"
#include "SHEMRMAggregator.hpp"
#include "TimedAggregator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"
#include "poros.h"

namespace poros
{

UNITTEST(AggregatorFactory, RandomMatchingAggregatorTest)
{
  RandomEngineHandle rand = RandomEngineFactory::make(0);

  std::unique_ptr<IAggregator> ptr = AggregatorFactory::make(RANDOM_MATCHING, \
      rand);

  RandomMatchingAggregator const * const rmPtr = \
      dynamic_cast<RandomMatchingAggregator*>(ptr.get());

  testTrue(rmPtr != nullptr);
}

UNITTEST(AggregatorFactory, SHEMRMAggregatorTest)
{
  RandomEngineHandle rand = RandomEngineFactory::make(0);

  std::unique_ptr<IAggregator> ptr = AggregatorFactory::make( \
      SORTED_HEAVY_EDGE_MATCHING, rand);

  SHEMRMAggregator const * const rmPtr = \
      dynamic_cast<SHEMRMAggregator*>(ptr.get());

  testTrue(rmPtr != nullptr);
}

UNITTEST(AggregatorFactory, TimedAggregatorTest)
{
  RandomEngineHandle rand = RandomEngineFactory::make(0);

  std::shared_ptr<TimeKeeper> timeKeeper(new TimeKeeper);

  std::unique_ptr<IAggregator> ptr = AggregatorFactory::make( \
      SORTED_HEAVY_EDGE_MATCHING, rand, timeKeeper);

  TimedAggregator const * const rmPtr = \
      dynamic_cast<TimedAggregator*>(ptr.get());

  testTrue(rmPtr != nullptr);
}

}
