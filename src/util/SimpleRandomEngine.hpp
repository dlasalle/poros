/**
* @file SimpleRandomEngine.hpp
* @brief The SimpleRandomEngine class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-20
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


#ifndef POROS_SRC_SIMPLERANDOMENGINE_HPP
#define POROS_SRC_SIMPLERANDOMENGINE_HPP

#include "Base.hpp"

#include <cstdint>
#include <random>
#include <algorithm>

namespace poros
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


