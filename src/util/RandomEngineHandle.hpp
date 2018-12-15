/**
 * @file RandomEngineHandle.hpp
 * @brief The RandomEngine handle class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-08-26
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


#ifndef POROS_SRC_RANDOMENGINEHANDLE_HPP
#define POROS_SRC_RANDOMENGINEHANDLE_HPP

#include "util/RandomEngine.hpp"

#include <memory>

namespace poros
{
  
class RandomEngineHandle
{
  public:
    /**
    * @brief Create a new random engine handle from a pointer to a random
    * engine. This handle becomes the new owner of the handle.
    *
    * @param randPtr The random engine.
    */
    explicit RandomEngineHandle(
        std::shared_ptr<RandomEngine> randPtr) :
      m_engine(randPtr)
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
    vtx_type randInRange(
        vtx_type const min,
        vtx_type const max)
    {
      return m_engine->randInRange(min, max);
    }

    /**
    * @brief Fill a vector with a vertex permutation.
    *
    * @param container The container.
    * @param start The starting vertex (inclusvie).
    * @param end The ending vertex (exclusive).
    */
    void fillWithPerm(
        vtx_type * const container,
        vtx_type const start,
        vtx_type const end)
    {
      return m_engine->fillWithPerm(container, start, end);
    }

    /**
    * @brief Set the random seed to use.
    *
    * @param seed The seed to use.
    */
    void setSeed(
        unsigned int seed)
    {
      m_engine->setSeed(seed);
    }

    /**
    * @brief Get the random engine of this handle.
    *
    * @return The random engine.
    */
    RandomEngine * get()
    {
      return m_engine.get();
    }

  private:
    std::shared_ptr<RandomEngine> m_engine;
};

}

#endif
