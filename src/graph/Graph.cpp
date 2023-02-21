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

#ifndef NDEBUG
#include <iostream>
#endif

namespace poros
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

template<typename T>
sl::ConstArray<T> emptyIfNull(
    T const * const ptr,
    size_t const size)
{
  if (ptr != nullptr) {
    return sl::ConstArray<T>(ptr, size);
  } else {
    return sl::ConstArray<T>(nullptr, 0);
  }
}
    


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
        emptyIfNull(vertexWeight, numVertices),
        emptyIfNull(edgeWeight, numEdges))
{
  // do nothing
}


Graph::Graph(
    sl::ConstArray<adj_type> edgePrefix,
    sl::ConstArray<vtx_type> edgeList,
    sl::ConstArray<wgt_type> vertexWeight,
    sl::ConstArray<wgt_type> edgeWeight) :
  m_unitEdgeWeight(true),
  m_unitVertexWeight(true),
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
    if (m_vertexWeight.size() == 0) {
      // allocate unit vertex weight
      m_unitVertexWeight = true;
      m_totalVertexWeight = static_cast<wgt_type>(m_numVertices);
    } else {
      for (vtx_type v = 0; v < m_numVertices; ++v) {
        const wgt_type vwgt = m_vertexWeight[v];
        m_totalVertexWeight += vwgt;

        if (vwgt != static_cast<wgt_type>(1)) {
          m_unitVertexWeight = false;
        }
      }
    }
  }

  // calculate total edge weight
  if (m_numEdges > 0) {
    if (m_edgeWeight.size() == 0) {
      // allocate unit edge weight
      m_unitEdgeWeight = true;
      m_totalEdgeWeight = static_cast<wgt_type>(m_numEdges);
    } else {
      for (adj_type e = 0; e < m_numEdges; ++e) {
        const wgt_type ewgt = m_edgeWeight[e];
        m_totalEdgeWeight += ewgt;

        if (ewgt != static_cast<wgt_type>(1)) {
          m_unitEdgeWeight = false;
        }
      }
    }
  }
}

Graph::Graph(
    sl::ConstArray<adj_type> edgePrefix,
    sl::ConstArray<vtx_type> edgeList,
    sl::ConstArray<wgt_type> vertexWeight,
    sl::ConstArray<wgt_type> edgeWeight,
    wgt_type const totalVertexWeight,
    wgt_type const totalEdgeWeight,
    bool const unitVertexWeight,
    bool const unitEdgeWeight) :
  m_unitEdgeWeight(unitEdgeWeight),
  m_unitVertexWeight(unitVertexWeight),
  m_numVertices(edgePrefix.size()-1),
  m_numEdges(edgeList.size()),
  m_totalVertexWeight(totalVertexWeight),
  m_totalEdgeWeight(totalEdgeWeight),
  m_edgePrefix(std::move(edgePrefix)),
  m_edgeList(std::move(edgeList)),
  m_vertexWeight(std::move(vertexWeight)),
  m_edgeWeight(std::move(edgeWeight))
{
}



Graph::Graph(
    Graph && lhs) noexcept :
  m_unitEdgeWeight(lhs.m_unitEdgeWeight),
  m_unitVertexWeight(lhs.m_unitVertexWeight),
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
  for (Vertex const v : vertices()) {
    if (hasUnitVertexWeight()) {
      vertexSum += weightOf<false>(v);
    } else {
      vertexSum += weightOf<true>(v);
    }
  }
  if (vertexSum != m_totalVertexWeight) {
    std::cerr << "Invalid vertex weight sum: Actual " << vertexSum <<
        " Expected: " << m_totalVertexWeight << std::endl;
    return false;
  }

  // check edge list
  for (Edge const e : edges()) {
    if (destinationOf(e) >= m_numVertices) {
      // invalid vertex
      std::cerr << "Invalid vertex: " << destinationOf(e) <<
          " / " << m_numVertices << std::endl;
      return false;
    }
  }

  // check edge weight sum
  wgt_type edgeSum = 0;
  for (Edge const e : edges()) {
    if (hasUnitEdgeWeight()) {
      edgeSum += weightOf<false>(e);
    } else {
      edgeSum += weightOf<true>(e);
    }
  }
  if (edgeSum != m_totalEdgeWeight) {
    std::cerr << "Invalid edge weight sum: Actual " << edgeSum << " Expected: "
        << m_totalEdgeWeight << std::endl;
    return false;
  }

  // check symmetry
  for (Vertex const v : vertices()) {
    for (Edge const e : edgesOf(v)) {
      // find reverse edge
      Vertex const u = destinationOf(e);
      bool found = false;
      for (Edge const f : edgesOf(u)) {
        if (v == destinationOf(f)) {
          if (!hasUnitEdgeWeight() && weightOf<true>(e) != weightOf<true>(f)) {
            std::cerr << "Edge weight is not symmetric " << e.index << ": " <<
                weightOf<true>(e) << " / " << weightOf<true>(f) << std::endl;
            return false;
          }
          found = true;
          break;
        }
      }
      if (!found) {
        std::cerr << "Did not find return edge for edge " << e.index
            << "(src " << v.index << ", dst " << destinationOf(e).index <<
            ")" << std::endl;
        return false;
      }
    }
  }

  return true;
}
#endif

}
