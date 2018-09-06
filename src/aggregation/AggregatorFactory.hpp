/**
* @file AggregatorFactory.hpp
* @brief The AggregatorFactory class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-09-04
*/


#ifndef DOLOS_SRC_AGGREGATORFACTORY_HPP
#define DOLOS_SRC_AGGREGATORFACTORY_HPP

#include "IAggregator.hpp"
#include "util/RandomEngineHandle.hpp"

#include <memory>

namespace dolos
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
      
      
};

}

#endif

