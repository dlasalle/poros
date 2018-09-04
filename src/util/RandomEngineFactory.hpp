/**
* @file RandomEngineFactor.hpp
* @brief The RandomEngineFactor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-09-04
*/

#ifndef DOLOS_SRC_RANDOMENGINEFACTORY_HPP
#define DOLOS_SRC_RANDOMENGINEFACTORY_HPP

#include "RandomEngineHandle.hpp"

namespace dolos
{

class RandomEngineFactory
{
  public:
  /**
  * @brief Create a new default random engine.
  *
  * @param seed The seed to use.
  *
  * @return The random engine.
  */
  static RandomEngineHandle make(
      unsigned int seed);

};

}

#endif


