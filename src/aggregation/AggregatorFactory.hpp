/**
* @file AggregatorFactory.hpp
* @brief The AggregatorFactory class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-09-04
*/


#ifndef POROS_SRC_AGGREGATORFACTORY_HPP
#define POROS_SRC_AGGREGATORFACTORY_HPP

#include "IAggregator.hpp"
#include "util/RandomEngineHandle.hpp"
#include "util/TimeKeeper.hpp"

#include <memory>

namespace poros
{

class AggregatorFactory
{
  public:
  /**
  * @brief Create a new aggregator.
  *
  * @param scheme The scheme for aggregation to use.
  * @param rng The random number engine.
  *
  * @return The instantiated aggregator.
  */
  static std::unique_ptr<IAggregator> make(
      int scheme,
      RandomEngineHandle rng);
      
  /**
  * @brief Create a new aggregator.
  *
  * @param scheme The scheme for aggregation to use.
  * @param rng The random number engine.
  * @param timeKeeper The time keeper to report times to.
  *
  * @return The instantiated aggregator.
  */
  static std::unique_ptr<IAggregator> make(
      int scheme,
      RandomEngineHandle rng,
      std::shared_ptr<TimeKeeper> timeKeeper);
  

};

}

#endif

