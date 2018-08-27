/**
* @file IRandomEngine.hpp
* @brief The IRandomEngine interface.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-19
*/



#ifndef DOLOS_SRC_IRANDOMENGINE_HPP
#define DOLOS_SRC_IRANDOMENGINE_HPP


#include "Base.hpp"

namespace dolos
{

class IRandomEngine 
{
  public:
  /**
  * @brief Virtual destructor.
  */
  virtual ~IRandomEngine()
  {
    // do nothing
  }

  /**
  * @brief Get a random number with the given minimum and maximum values.
  *
  * @param min The minimum value (inclusive).
  * @param max The maximum value (inclusive).
  *
  * @return The random number.
  */
  virtual vtx_type randInRange(
      vtx_type const min,
      vtx_type const max) = 0;

  /**
  * @brief Fill a vector with a vertex permutation.
  *
  * @param container The container.
  * @param start The starting vertex (inclusvie).
  * @param end The ending vertex (exclusive).
  */
  virtual void fillWithPerm(
      vtx_type * container,
      vtx_type const start,
      vtx_type const end) = 0;

  /**
  * @brief Set the random seed to use.
  *
  * @param seed The seed.
  */
  virtual void setSeed(
      unsigned int seed) = 0;

};

}

#endif
