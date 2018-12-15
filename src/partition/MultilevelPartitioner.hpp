/**
 * @file MultilevelPartitioner.hpp
 * @brief The MultilevelPartitioner class.
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


#ifndef POROS_SRC_MULTILEVELPARTITIONER_HPP
#define POROS_SRC_MULTILEVELPARTITIONER_HPP


#include "partition/IPartitioner.hpp"
#include "partition/IRefiner.hpp"
#include "aggregation/IAggregator.hpp"

#include <memory>

namespace poros
{


class MultilevelPartitioner :
    public IPartitioner
{
  public:
    /**
    * @brief Create a new mutilevel partitioner. 
    *
    * @param aggregator The aggregation algorithm to use.
    * @param initialPartitioner The initial partitioning algorithm to use.
    * @param refiner The refinement algorithm to use.
    */
    MultilevelPartitioner(
        std::unique_ptr<IAggregator> aggregator,
        std::unique_ptr<IPartitioner> initialPartitioner,
        std::unique_ptr<IRefiner> refiner);

    /**
     * @brief Create a partitioning of the graph.
     *
     * @param target The target partitioning to achieve.
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    virtual Partitioning execute(
        TargetPartitioning const * target,
        Graph const * graph) override;

  private:
    std::unique_ptr<IAggregator> m_aggregator;
    std::unique_ptr<IPartitioner> m_initialPartitioner;
    std::unique_ptr<IRefiner> m_refiner;
     
};

}

#endif
