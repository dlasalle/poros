/**
 * @file IMappedGraph.hpp
 * @brief The IMappedGraph interface.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018
 * @version 1
 * @date 2017-10-17
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




#ifndef POROS_SRC_IMAPPEDGRAPH_HPP
#define POROS_SRC_IMAPPEDGRAPH_HPP


#include "graph/Graph.hpp"
#include "partition/Partitioning.hpp"

namespace poros
{


class IMappedGraph
{
  public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~IMappedGraph()
    {
      // do nothing
    }


    /**
     * @brief Get the underyling graph.
     *
     * @return The graph.
     */
    virtual Graph const * getGraph() const = 0;


    /**
     * @brief Map a sub partitioning of this graph to some other super
     * partitioning.
     *
     * @param subPartitioning The partitioning of this graph.
     * @param partitionLabels The labels to have the mapped partitioning
     * written to.
     * @param offset The offset of partition IDs in the subgraph compared to
     * the super graph.
     */
    virtual void mapPartitioning(
        Partitioning const * subPartitioning,
        pid_type * partitionLabels,
        pid_type offset) const = 0;
};


}

#endif
