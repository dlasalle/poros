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

#include "Base.hpp"

#include <cstdint>
#include <random>
#include <algorithm>

namespace dolos
{


class SimpleRandomEngine
{
  public:
  using result_type = uint32_t;

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
      vtx_type const end);


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
      vtx_type const max)
  {
    return std::uniform_int_distribution<vtx_type>(min, max)(m_rng);
  }


  /**
  * @brief The minimum value returned from the () operator.
  *
  * @return The minimum value.
  */
  result_type min() const
  {
    return m_rng.min();
  }


  /**
  * @brief The maximum value return from dthe () operator.
  *
  * @return The maximum value.
  */
  result_type max() const
  {
    return m_rng.max();
  }


  /**
  * @brief Generate a random number between min() and max().
  *
  * @return The random number.
  */
  result_type operator()()
  {
    return m_rng();
  }


  /**
  * @brief Set the random seed to use.
  *
  * @param seed The seed to use.
  */
  void setSeed(
      unsigned int seed);


  private:
  std::mt19937 m_rng;
};

}

#endif


