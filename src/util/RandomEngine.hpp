/**
* @file RandomEngine.hpp
* @brief The RandomEngine class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-09-08
*/


#ifndef SRC_RANDOMENGINE_HPP
#define SRC_RANDOMENGINE_HPP

#include "SimpleRandomEngine.hpp"

namespace dolos
{

class RandomEngine : public SimpleRandomEngine
{
  public:
  /**
  * @brief Create a new random engine with the given seed.
  *
  * @param seed The seed.
  */
  RandomEngine(
      unsigned int const seed) :
    SimpleRandomEngine(seed)
  {
    // do nothing
  }
};

}


#endif
