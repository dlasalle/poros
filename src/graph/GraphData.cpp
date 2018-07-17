/**
* @file GraphData.cpp
* @brief Implementation of the GraphData class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/


#include "GraphData.hpp"
#include "solidutils/Alloc.hpp"
#include "solidutils/Debug.hpp"


namespace dolos
{

/******************************************************************************
* CONSTANTS *******************************************************************
******************************************************************************/

namespace
{

constexpr const wgt_type UNIT_WEIGHT = static_cast<wgt_type>(1);

}


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


GraphData::GraphData(
    std::vector<adj_type> edgePrefix,
    std::vector<vtx_type> edgeList,
    std::vector<wgt_type> vertexWeight,
    std::vector<wgt_type> edgeWeight) :
  m_edgePrefix(std::move(edgePrefix)),
  m_edgeList(std::move(edgeList)),
  m_vertexWeight(std::move(vertexWeight)),
  m_edgeWeight(std::move(edgeWeight))
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


vtx_type GraphData::numVertices() const
{
  ASSERT_GREATER(m_edgePrefix.size(),0);

  vtx_type const numVertices = m_edgePrefix.size()-1;

  ASSERT_EQUAL(m_vertexWeight.size(), numVertices);

  return numVertices;
}


adj_type GraphData::numEdges() const
{
  adj_type const numEdges = m_edgePrefix.back();
  ASSERT_LESSEQUAL(numEdges, m_edgeWeight.size());

  return numEdges;
}


ConstantGraph GraphData::toGraph()
{
  GraphData * const data = new GraphData(std::move(*this));

  ConstantGraph graph( \
      data->numVertices(), data->numEdges(), \
      data->edgePrefix(), data->edgeList(), data->vertexWeight(), \
      data->edgeWeight(), data);

  return graph;
}


void GraphData::setUnitVertexWeight() noexcept
{
  m_vertexWeight.assign(m_vertexWeight.size(), UNIT_WEIGHT);
}


void GraphData::setUnitEdgeWeight() noexcept
{
  m_edgeWeight.assign(m_edgeWeight.size(), UNIT_WEIGHT);
}


adj_type * GraphData::edgePrefix() noexcept
{
  return m_edgePrefix.data();
}


vtx_type * GraphData::edgeList() noexcept
{
  return m_edgeList.data();
}


wgt_type * GraphData::vertexWeight() noexcept
{
  return m_vertexWeight.data();
}


wgt_type * GraphData::edgeWeight() noexcept
{
  return m_edgeWeight.data();
}


adj_type const * GraphData::edgePrefix() const noexcept
{
  return m_edgePrefix.data();
}


vtx_type const * GraphData::edgeList() const noexcept
{
  return m_edgeList.data();
}


wgt_type const * GraphData::vertexWeight() const noexcept
{
  return m_vertexWeight.data();
}


wgt_type const * GraphData::edgeWeight() const noexcept
{
  return m_edgeWeight.data();
}


}
