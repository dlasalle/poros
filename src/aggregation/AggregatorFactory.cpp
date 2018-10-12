/**
 * @file AggregatorFactory.cpp
 * @brief Implementation of the AggregatorFactory class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-09-04
 */

#include "AggregatorFactory.hpp"
#include "RandomMatchingAggregator.hpp"
#include "SHEMRMAggregator.hpp"
#include "TimedAggregator.hpp"

#include "dolos.h"

#include "solidutils/Exception.hpp"


namespace dolos
{


/******************************************************************************
* PUBLIC STATIC METHODS *******************************************************
******************************************************************************/

std::unique_ptr<IAggregator> AggregatorFactory::make(
    int const scheme,
    RandomEngineHandle rng)
{
  std::unique_ptr<IAggregator> ptr;
  if (scheme == RANDOM_MATCHING) {
    ptr.reset(new RandomMatchingAggregator(rng));
  } else if (scheme == SORTED_HEAVY_EDGE_MATCHING) {
    ptr.reset(new SHEMRMAggregator(rng));
  } else {
    throw sl::InvalidInputException("Unknown aggregation scheme: " +
        std::to_string(scheme));
  }

  return ptr;
}


std::unique_ptr<IAggregator> AggregatorFactory::make(
    int const scheme,
    RandomEngineHandle rng,
    std::shared_ptr<TimeKeeper> timeKeeper)
{
  std::unique_ptr<TimedAggregator> ptr(new TimedAggregator(make(scheme, rng)));
  ptr->setTimeKeeper(timeKeeper);

  return ptr;
}
}
