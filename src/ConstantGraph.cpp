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
#include "ConstantGraph.hpp"


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
  ASSERT_NOTNULL(m_edgeList);
  ASSERT_NOTNULL(m_vertexWeight);
  ASSERT_NOTNULL(m_edgeWeight);

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


}
