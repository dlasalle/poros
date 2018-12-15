/**
* @file TwoWayRefinerFactory.hpp
* @brief The TwoWayRefinerFactory class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
*/



#ifndef POROS_SRC_TWOWAYREFINERFACTORY_HPP
#define POROS_SRC_TWOWAYREFINERFACTORY_HPP

#include "ITwoWayRefiner.hpp"
#include "util/TimeKeeper.hpp"

#include <memory>

namespace poros
{

class TwoWayRefinerFactory
{
  public:
  /**
  * @brief Create a new ITwoWayRefiner object.
  *
  * @param scheme The scheme to instantiate.
  *
  * @return The instantiated scheme.
  */
  static std::unique_ptr<ITwoWayRefiner> make(
      int scheme);

  /**
  * @brief Create a new ITwoWayRefiner object.
  *
  * @param scheme The scheme to instantiate.
  * @param timeKeeper The TimeKeeper to report time to.
  *
  * @return The instantiated scheme.
  */
  static std::unique_ptr<ITwoWayRefiner> make(
      int scheme,
      std::shared_ptr<TimeKeeper> timeKeeper);
};


}

#endif
