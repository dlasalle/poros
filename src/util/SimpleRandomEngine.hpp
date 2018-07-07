/**
* @file SimpleRandomEngine.hpp
* @brief The SimpleRandomEngine class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-20
*/


#ifndef DOLOS_SRC_SIMPLERANDOMENGINE_HPP
#define DOLOS_SRC_SIMPLERANDOMENGINE_HPP


#include "IRandomEngine.hpp"
#include <random>

namespace dolos
{


class SimpleRandomEngine : public IRandomEngine
{
  public:
  /**
  * @brief Create a new random engine.
  *
  * @param seed The seed to use.
  */
  SimpleRandomEngine(
      unsigned int seed = 0);

  /**
  * @brief Fill a vector with a vertex permutation.
  *
  * @param container The container.
  * @param start The starting vertex (inclusvie).
  * @param end The ending vertex (exclusive).
  */
  void fillWithPerm(
      vtx_type * container,
      vtx_type const start,
      vtx_type const end) override;


  /**
  * @brief Get a random number with the given minimum and maximum values.
  *
  * @param min The minimum value (inclusive).
  * @param max The maximum value (inclusive).
  *
  * @return The random number.
  */
  vtx_type randInRange(
      vtx_type const min,
      vtx_type const max) override;


  private:
  std::mt19937 m_rng;
};

}

#endif


