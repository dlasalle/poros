/**
 * @file AggregatorFactory.cpp
 * @brief Implementation of the AggregatorFactory class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-09-04
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

#include "poros.h"
#include <stdexcept>


namespace poros
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
    throw std::runtime_error("Unknown aggregation scheme: " +
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
