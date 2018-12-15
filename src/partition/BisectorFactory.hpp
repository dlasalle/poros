/**
* @file BisectorFactory.hpp
* @brief The BisectorFactory class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
*/



#ifndef POROS_SRC_BISECTORFACTORY_HPP
#define POROS_SRC_BISECTORFACTORY_HPP

#include "IBisector.hpp"
#include "util/RandomEngineHandle.hpp"
#include "util/TimeKeeper.hpp"

#include <memory>

namespace poros
{

class BisectorFactory
{
  // TODO: replace scheme and numBisections with a BisectionParameters
  public:
  /**
  * @brief Create a new bisector.
  *
  * @param scheme The scheme for bisection to use.
  * @param rng The random number engine.
  * @param numBisection The number of bisections to make.
  *
  * @return The instantiated bisector.
  */
  static std::unique_ptr<IBisector> make(
      int scheme,
      RandomEngineHandle rng,
      int numBisections);
      
  /**
  * @brief Create a new bisector.
  *
  * @param scheme The scheme for bisection to use.
  * @param rng The random number engine.
  * @param numBisection The number of bisections to make.
  * @param timeKeeper The time keeper to report times to.
  *
  * @return The instantiated bisector.
  */
  static std::unique_ptr<IBisector> make(
      int scheme,
      RandomEngineHandle rng,
      int numBisections,
      std::shared_ptr<TimeKeeper> timeKeeper);
  


  
};

}

#endif
