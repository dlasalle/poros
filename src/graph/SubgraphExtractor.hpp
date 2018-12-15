/**
* @file SubgraphExtractor.hpp
* @brief The SubgraphExtractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-10
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




#ifndef POROS_SRC_SUBGRAPHEXTRACTOR_HPP
#define POROS_SRC_SUBGRAPHEXTRACTOR_HPP


#include "graph/Graph.hpp"
#include "partition/Partitioning.hpp"
#include "graph/Subgraph.hpp"


namespace poros
{

class SubgraphExtractor
{
  public:
    /**
    * @brief Extract the subgraph formed by each partition.
    *
    * @param graph The graph.
    * @param part The partitioning.
    * @param labels The labels of the vertices in the graph (may be null if
    * they are not aliased).
    *
    * @return The subgraphs.
    */
    static std::vector<Subgraph> partitions(
        Graph const * graph,
        Partitioning const * part,
        vtx_type const * const labels = nullptr);
};


}


#endif
