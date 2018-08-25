/**
* @file ConstantGraph.cpp
* @brief The implementation of the ConstantGraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/



#include "Base.hpp"
#include "solidutils/Debug.hpp"
#include "graph/ConstantGraph.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


ConstantGraph::ConstantGraph(
    vtx_type numVertices,
    adj_type numEdges,
    adj_type const * const edgePrefix,
    vtx_type const * const edgeList,
    wgt_type const * const vertexWeight,
    wgt_type const * const edgeWeight,
    IAllocatedData * const data) :
  m_numVertices(numVertices),
  m_numEdges(numEdges),
  m_totalVertexWeight(0),
  m_totalEdgeWeight(0),
  m_edgePrefix(edgePrefix),
  m_edgeList(edgeList),
  m_vertexWeight(vertexWeight),
  m_edgeWeight(edgeWeight),
  m_data(data)
{
  ASSERT_NOTNULL(m_edgePrefix);

  // calculate total vertex weight
  for (vtx_type v = 0; v < m_numVertices; ++v) {
    m_totalVertexWeight += m_vertexWeight[v];
  }

  // calculate total  edge weight
  for (adj_type e = 0; e < m_numEdges; ++e) {
    m_totalEdgeWeight += m_edgeWeight[e];
  }
}


ConstantGraph::ConstantGraph(
    ConstantGraph && lhs) noexcept :
  m_numVertices(lhs.m_numVertices),
  m_numEdges(lhs.m_numEdges),
  m_totalVertexWeight(lhs.m_totalVertexWeight),
  m_totalEdgeWeight(lhs.m_totalEdgeWeight),
  m_edgePrefix(lhs.m_edgePrefix),
  m_edgeList(lhs.m_edgeList),
  m_vertexWeight(lhs.m_vertexWeight),
  m_edgeWeight(lhs.m_edgeWeight),
  m_data(lhs.m_data)
{
  // destrory old graph's data
  lhs.m_numVertices = 0;
  lhs.m_numEdges = 0;
  lhs.m_totalVertexWeight = 0;
  lhs.m_totalEdgeWeight = 0;
  lhs.m_edgePrefix = nullptr;
  lhs.m_edgeList = nullptr;
  lhs.m_vertexWeight = nullptr;
  lhs.m_edgeWeight = nullptr;
  lhs.m_data = nullptr;
}


ConstantGraph::~ConstantGraph()
{
  if (m_data) {
    // if we're responsible for free the data, do so.
    delete m_data;
  }
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

CSRGraphData ConstantGraph::getData() const noexcept
{
  return CSRGraphData(m_edgePrefix, m_edgeList, m_vertexWeight, m_edgeWeight);
}

bool ConstantGraph::isValid() const
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

}
