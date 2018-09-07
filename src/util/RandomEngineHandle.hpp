/**
 * @file RandomEngineHandle.hpp
 * @brief The RandomEngine handle class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-08-26
 */


#ifndef DOLOS_SRC_RANDOMENGINEHANDLE_HPP
#define DOLOS_SRC_RANDOMENGINEHANDLE_HPP

#include "util/IRandomEngine.hpp"

#include <memory>

namespace dolos
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
        IRandomEngine * const randPtr) :
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
    IRandomEngine * get()
    {
      return m_engine.get();
    }

  private:
    std::shared_ptr<IRandomEngine> m_engine;
};

}

#endif
