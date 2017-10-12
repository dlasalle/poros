/**
* @file GraphData.cpp
* @brief Implementation of the GraphData class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/


#include "Alloc.hpp"
#include "Debug.hpp"
#include "GraphData.hpp"

namespace dolos
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


GraphData::GraphData(
    vtx_type const numVertices,
    adj_type const numEdges) :
  m_edgePrefix(numVertices+1),
  m_edgeList(numEdges),
  m_vertexWeight(numVertices),
  m_edgeWeight(numEdges)
{
  // do nothing
}


// while the default would suit us just fine (aside from the missing noexcept),
// debugging generated constructors is not really do-able. One reason to go
// back to the default, is that any added fields to this class will require
// modification of this constructor. 
GraphData::GraphData(
    GraphData && lhs) noexcept :
  m_edgePrefix(std::move(lhs.m_edgePrefix)),
  m_edgeList(std::move(lhs.m_edgeList)),
  m_vertexWeight(std::move(lhs.m_vertexWeight)),
  m_edgeWeight(std::move(lhs.m_edgeWeight))
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


vtx_type GraphData::getNumVertices() const
{
  ASSERT_GREATER(m_edgePrefix.size(),0);

  vtx_type const numVertices = m_edgePrefix.size()-1;

  ASSERT_EQUAL(m_vertexWeight.size(), numVertices);

  return numVertices;
}


adj_type GraphData::getNumEdges() const
{
  adj_type const numEdges = m_edgeList.size();
  ASSERT_EQUAL(m_edgeWeight.size(), numEdges);

  return numEdges;
}


ConstantGraph GraphData::toGraph()
{
  GraphData * const data = new GraphData(std::move(*this));

  ConstantGraph graph( \
      data->getNumVertices(), data->getNumEdges(), \
      data->getEdgePrefix(), data->getEdgeList(), data->getVertexWeight(), \
      data->getEdgeWeight(), data);

  return graph;
}


void GraphData::setUnitVertexWeight() noexcept
{
  m_vertexWeight.set(1);
}


void GraphData::setUnitEdgeWeight() noexcept
{
  m_edgeWeight.set(1);
}


adj_type * GraphData::getEdgePrefix() noexcept
{
  return m_edgePrefix.data();
}


vtx_type * GraphData::getEdgeList() noexcept
{
  return m_edgeList.data();
}


wgt_type * GraphData::getVertexWeight() noexcept
{
  return m_vertexWeight.data();
}


wgt_type * GraphData::getEdgeWeight() noexcept
{
  return m_edgeWeight.data();
}


adj_type const * GraphData::getEdgePrefix() const noexcept
{
  return m_edgePrefix.data();
}


vtx_type const * GraphData::getEdgeList() const noexcept
{
  return m_edgeList.data();
}


wgt_type const * GraphData::getVertexWeight() const noexcept
{
  return m_vertexWeight.data();
}


wgt_type const * GraphData::getEdgeWeight() const noexcept
{
  return m_edgeWeight.data();
}


}
