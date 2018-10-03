/**
* @file AggregatorFactory_test.cpp
* @brief The unit test for the AggregatorFactory class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-09-06
*/

#include "AggregatorFactory.hpp"
#include "RandomMatchingAggregator.hpp"
#include "HeavyEdgeMatchingAggregator.hpp"
#include "TimedAggregator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"
#include "dolos.h"

namespace dolos
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

UNITTEST(AggregatorFactory, HeavyEdgeMatchingAggregatorTest)
{
  RandomEngineHandle rand = RandomEngineFactory::make(0);

  std::unique_ptr<IAggregator> ptr = AggregatorFactory::make( \
      SORTED_HEAVY_EDGE_MATCHING, rand);

  HeavyEdgeMatchingAggregator const * const rmPtr = \
      dynamic_cast<HeavyEdgeMatchingAggregator*>(ptr.get());

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
