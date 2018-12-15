/**
* @file Graph.cpp
* @brief The implementation of the Graph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-09
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



#include "Base.hpp"
#include "graph/Graph.hpp"
#include "solidutils/Debug.hpp"
#include "solidutils/Array.hpp"


namespace poros
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


Graph::Graph(
    vtx_type numVertices,
    adj_type numEdges,
    adj_type const * const edgePrefix,
    vtx_type const * const edgeList,
    wgt_type const * const vertexWeight,
    wgt_type const * const edgeWeight) :
  Graph(sl::ConstArray<adj_type>(edgePrefix, numVertices+1),
        sl::ConstArray<vtx_type>(edgeList, numEdges),
        sl::ConstArray<wgt_type>(vertexWeight, numVertices),
        sl::ConstArray<wgt_type>(edgeWeight, numEdges))
{
  // do nothing
}


Graph::Graph(
    sl::ConstArray<adj_type> edgePrefix,
    sl::ConstArray<vtx_type> edgeList,
    sl::ConstArray<wgt_type> vertexWeight,
    sl::ConstArray<wgt_type> edgeWeight) :
  m_uniformEdgeWeight(true),
  m_uniformVertexWeight(true),
  m_numVertices(edgePrefix.size()-1),
  m_numEdges(edgeList.size()),
  m_totalVertexWeight(0),
  m_totalEdgeWeight(0),
  m_edgePrefix(std::move(edgePrefix)),
  m_edgeList(std::move(edgeList)),
  m_vertexWeight(std::move(vertexWeight)),
  m_edgeWeight(std::move(edgeWeight))
{
  // calculate total vertex weight
  if (m_numVertices > 0) {
    if (m_vertexWeight.data() == nullptr) {
      // allocate uniform vertex weight
      m_vertexWeight = sl::Array<vtx_type>(m_numVertices, 1);
      m_uniformVertexWeight = true;
    } else {
      const wgt_type baseVertexWeight = m_vertexWeight[0];
      for (vtx_type v = 0; v < m_numVertices; ++v) {
        const wgt_type vwgt = m_vertexWeight[v];
        m_totalVertexWeight += vwgt;

        if (vwgt != baseVertexWeight) {
          m_uniformVertexWeight = false;
        }
      }
    }
  }

  // calculate total edge weight
  if (m_numEdges > 0) {
    if (m_edgeWeight.data() == nullptr) {
      // allocate uniform edge weight
      m_edgeWeight = sl::Array<wgt_type>(m_numEdges, 1);
      m_uniformEdgeWeight = true;
    } else {
      const wgt_type baseEdgeWeight = m_edgeWeight[0];
      for (adj_type e = 0; e < m_numEdges; ++e) {
        const wgt_type ewgt = m_edgeWeight[e];
        m_totalEdgeWeight += ewgt;

        if (ewgt != baseEdgeWeight) {
          m_uniformEdgeWeight = false;
        }
      }
    }
  }
}




Graph::Graph(
    Graph && lhs) noexcept :
  m_uniformEdgeWeight(lhs.m_uniformEdgeWeight),
  m_uniformVertexWeight(lhs.m_uniformVertexWeight),
  m_numVertices(lhs.m_numVertices),
  m_numEdges(lhs.m_numEdges),
  m_totalVertexWeight(lhs.m_totalVertexWeight),
  m_totalEdgeWeight(lhs.m_totalEdgeWeight),
  m_edgePrefix(std::move(lhs.m_edgePrefix)),
  m_edgeList(std::move(lhs.m_edgeList)),
  m_vertexWeight(std::move(lhs.m_vertexWeight)),
  m_edgeWeight(std::move(lhs.m_edgeWeight))
{
  // destrory old graph's data
  lhs.m_numVertices = 0;
  lhs.m_numEdges = 0;
  lhs.m_totalVertexWeight = 0;
  lhs.m_totalEdgeWeight = 0;
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

#ifndef NDEBUG
bool Graph::isValid() const
{
  // check vertex weight sum
  wgt_type vertexSum = 0;
  for (vtx_type i = 0; i < m_numVertices; ++i) {
    vertexSum += m_vertexWeight[i];
  }
  if (vertexSum != m_totalVertexWeight) {
    return false;
  }

  // check edge list
  for (adj_type i = 0; i < m_numEdges; ++i) {
    if (m_edgeList[i] >= m_numVertices) {
      // invalid vertex
      return false;
    }
  }

  // check edge weight sum
  wgt_type edgeSum = 0;
  for (adj_type i = 0; i < m_numEdges; ++i) {
    edgeSum += m_edgeWeight[i];
  }
  if (edgeSum != m_totalEdgeWeight) {
    return false;
  }

  // check symmetry
  for (vtx_type v = 0; v < m_numVertices; ++v) {
    for (adj_type j = m_edgePrefix[v]; j < m_edgePrefix[v+1]; ++j) {
      // find reverse edge
      vtx_type const u = m_edgeList[j];
      bool found = false;
      for (adj_type k = m_edgePrefix[u]; k < m_edgePrefix[u+1]; ++k) {
        if (v == m_edgeList[k]) {
          if (m_edgeWeight[k] != m_edgeWeight[j]) {
            return false;
          }
          found = true;
          break;
        }
      }
      if (!found) {
        return false;
      }
    }
  }

  return true;
}
#endif

}
