/**
 * @file RandomBisector.hpp
 * @brief A class for creating a random bisection.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018
 * @version 1
 * @date 2017-10-04
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


#ifndef POROS_SRC_RANDOMBISECTOR_HPP
#define POROS_SRC_RANDOMBISECTOR_HPP


#include "IBisector.hpp"
#include "PartitionParameters.hpp"
#include "util/RandomEngineHandle.hpp"


namespace poros
{


class RandomBisector :
  public IBisector
{
  public:
    /**
     * @brief Create a new random partitioner with the given parameters.
     *
     * @param randEngine The random engine.
     */
    RandomBisector(
        RandomEngineHandle randEngine);


    /**
    * @brief Deleted copy constructor.
    *
    * @param rhs The bisector to copy.
    */
    RandomBisector(
        RandomBisector const & rhs) = delete;


    /**
    * @brief Deleted assignment operator.
    *
    * @param rhs The bisector to assign.
    */
    RandomBisector operator=(
        RandomBisector const & rhs) = delete;


    /**
     * @brief Destructor.
     */
    virtual ~RandomBisector();


    /**
     * @brief Randomly assign vertices to partitions.
     *
     * @param target The target partitioning to achieve.
     * @param graph The graph.
     *
     * @return The assigned partitioning.
     */
    virtual Partitioning execute(
        TargetPartitioning const * target,
        Graph const * graph) override;


  private:
  RandomEngineHandle m_randEngine;
};


}


#endif
