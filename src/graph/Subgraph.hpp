/**
* @file Subgraph.hpp
* @brief The Subgraph class.
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




#ifndef POROS_SRC_SUBGRAPH_HPP
#define POROS_SRC_SUBGRAPH_HPP


#include "graph/GraphHandle.hpp"
#include "partition/Partitioning.hpp"
#include "graph/IMappedGraph.hpp"
#include "solidutils/Array.hpp"


namespace poros
{

class Subgraph :
    public IMappedGraph
{
  public:
    /**
    * @brief Create a new subgraph.
    *
    * @param superGraph The super graph.
    * @param superMap The mapping of vertices to the super graph.
    */
    Subgraph(
        GraphHandle superGraph,
        sl::Array<vtx_type> superMap);


    /**
    * @brief Create a new subgraph with a mapping which maps vertices to
    * themselves.
    *
    * @param superGraph The super graph.
    */
    Subgraph(
        GraphHandle superGraph);


    /**
    * @brief Get the underlying graph.
    *
    * @return The graph.
    */
    Graph const * getGraph() const override;


    /**
    * @brief Get the mapping of the vertices back to the super graph vertices.
    *
    * @return The mapping.
    */
    vtx_type const * getSuperMap() const;


    /**
     * @brief Map a sub partitioning of this graph to some other super
     * partitioning.
     *
     * @param subPartitioning The partitioning of this graph.
     * @param partitionLabels The partition labels of the super graph (output).
     * @param offset The offset of partition IDs in the subgraph compared to
     * the super graph.
     */
    void mapPartitioning(
        Partitioning const * subPartitioning,
        pid_type * partitionLabels,
        pid_type offset) const override;


    /**
     * @brief Get the vertex index in the super graph of a vertex in this
     * subgraph.
     *
     * @param vertex The vertex this subgraph.
     *
     * @return The vertex id in the super graph.
     */
    vtx_type getSuperMap(
        vtx_type const vertex) const noexcept
    {
      return m_superMap[vertex];
    }


  private:
    sl::Array<vtx_type> m_superMap;
    GraphHandle m_graph;
};


}

#endif
