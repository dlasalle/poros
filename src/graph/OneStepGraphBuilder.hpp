/**
* @file OneStepGraphBuilder.hpp
* @brief The OneStepGraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-01-18
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




#ifndef POROS_SRC_ONESTEPGRAPHBUILDER_HPP
#define POROS_SRC_ONESTEPGRAPHBUILDER_HPP


#include "graph/GraphHandle.hpp"
#include "Base.hpp"
#include "solidutils/Array.hpp"

#include <vector>


namespace poros
{


class OneStepGraphBuilder
{
  public:
  /**
  * @brief Create a new graph builder.
  *
  * @param numVertices The number of vertices in the new graph.
  * @param maxNumEdges The maximum number of edges in the coarse graph.
  */
  OneStepGraphBuilder(
      vtx_type numVertices,
      adj_type maxNumEdges);

  /**
  * @brief Add an edge to the current vertex.
  *
  * @param dest The destination of the edge.
  * @param wgt The weight of the edge.
  */
  inline void addEdge(
      vtx_type const dest,
      wgt_type const wgt)
  {
    adj_type const idx = m_htable[dest];
    if (idx == NULL_ADJ) {
      m_htable[dest] = static_cast<adj_type>(m_numEdges);
      m_edgeList[m_numEdges] = dest;
      m_edgeWeight[m_numEdges] = wgt;
      ++m_numEdges;
    } else {
      m_edgeWeight[idx] += wgt;
    }

    m_totalEdgeWeight += wgt;
  }

  /**
  * @brief Perform bookkeeping for a vertex that will no longer have edges
  * added.
  *
  * @param wgt The weight of the vertex.
  */
  inline void finishVertex(
        vtx_type const vertexWeight)
  {
    vtx_type const thisVtx = m_numVertices;
    // clear self loop
    m_htable[thisVtx] = NULL_ADJ;

    ++m_numVertices;

    adj_type const start = m_edgePrefix[thisVtx];
    for (vtx_type j = start; j < m_numEdges; ++j) {
      vtx_type const u = m_edgeList[j];
      ASSERT_LESS(u, m_htable.size());
      m_htable[u] = NULL_ADJ;
    }

    m_totalVertexWeight += vertexWeight;
    m_vertexWeight[thisVtx] = vertexWeight;
    m_edgePrefix[m_numVertices] = m_numEdges;

    // set next self-loop
    m_htable[m_numVertices] = m_maxNumEdges;
  }

  /**
  * @brief Build the graph. This resets the builder to its initial state.
  *
  * @return The built graph.
  */
  GraphHandle finish();

  private:
    vtx_type m_numVertices;
    adj_type m_numEdges;
    sl::Array<adj_type> m_edgePrefix;
    sl::Array<vtx_type> m_edgeList;
    sl::Array<wgt_type> m_vertexWeight;
    sl::Array<wgt_type> m_edgeWeight;

    wgt_type m_totalVertexWeight;
    wgt_type m_totalEdgeWeight;

    std::vector<adj_type> m_htable;

    adj_type m_maxNumEdges;

    // prevent copying
    OneStepGraphBuilder(
        OneStepGraphBuilder const & lhs) = delete;
    OneStepGraphBuilder & operator=(
        OneStepGraphBuilder const & lhs) = delete;



};


}


#endif
