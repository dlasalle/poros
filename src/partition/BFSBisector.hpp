/**
* @file BFSBisector.hpp
* @brief The BFSBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-04
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


#ifndef POROS_SRC_BFSBISECTOR_HPP
#define POROS_SRC_BFSBISECTOR_HPP

#include "IBisector.hpp"
#include "util/RandomEngineHandle.hpp"

namespace poros
{

class BFSBisector : public IBisector
{
  public:
    /**
    * @brief Create a new BFSBisector.
    *
    * @param rng The random engine to use.
    */
    BFSBisector(
        RandomEngineHandle rng);

    /**
    * @brief Deleted copy constructor.
    *
    * @param rhs The bisector to copy.
    */
    BFSBisector(
        BFSBisector const & rhs) = delete;

    /**
    * @brief Deleted assignment operator.
    *
    * @param rhs The bisector to assign from.
    *
    * @return This bisector.
    */
    BFSBisector& operator=(
        BFSBisector const & rhs) = delete;

    /**
     * @brief Create a two-way partitioning of the graph via weighted BFS.
     *
     * @param target The target partitioning to achieve.
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    virtual Partitioning execute(
        TargetPartitioning const * target,
        Graph const * graph) override;


    /**
    * @brief Create a two-way partitioning of the graph via weighted BFS with
    * the given seed vertex.
    *
    * @param target The taget partitioning.
    * @param graph The graph.
    * @param seedVertex The seed vertex.
    *
    * @return The partitioning.
    */
    virtual Partitioning execute(
        TargetPartitioning const * target,
        Graph const * graph,
        Vertex const seedVertex);

  private:
    RandomEngineHandle m_rng;

};

}


#endif
