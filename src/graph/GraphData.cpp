/**
* @file GraphData.cpp
* @brief Implementation of the GraphData class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
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
  m_numVertices(numVertices),    
  m_numEdges(numEdges),
  m_edgePrefix(new adj_type[numVertices+1]),
  m_edgeList(new vtx_type[numEdges]),
  m_vertexWeight(new wgt_type[numVertices]),
  m_edgeWeight(new wgt_type[numEdges])
{
  // do nothing
}


GraphData::GraphData(
    vtx_type const numVertices,
    adj_type const numEdges,
    std::unique_ptr<adj_type[]> edgePrefix,
    std::unique_ptr<vtx_type[]> edgeList,
    std::unique_ptr<wgt_type[]> vertexWeight,
    std::unique_ptr<wgt_type[]> edgeWeight) :
  m_numVertices(numVertices),    
  m_numEdges(numEdges),
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
  m_numVertices(lhs.m_numVertices),
  m_numEdges(lhs.m_numEdges),
  m_edgePrefix(std::move(lhs.m_edgePrefix)),
  m_edgeList(std::move(lhs.m_edgeList)),
  m_vertexWeight(std::move(lhs.m_vertexWeight)),
  m_edgeWeight(std::move(lhs.m_edgeWeight))
{
  lhs.m_numVertices = 0;
  lhs.m_numEdges = 0;
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


vtx_type GraphData::numVertices() const
{
  return m_numVertices;
}


adj_type GraphData::numEdges() const
{
  return m_numEdges;
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
  m_vertexWeight.reset(new wgt_type[m_numVertices]);
  std::fill(m_vertexWeight.get(), m_vertexWeight.get()+m_numVertices, \
      UNIT_WEIGHT);
}


void GraphData::setUnitEdgeWeight() noexcept
{
  m_edgeWeight.reset(new wgt_type[m_numEdges]);
  std::fill(m_edgeWeight.get(), m_edgeWeight.get()+m_numEdges, UNIT_WEIGHT);
}


adj_type * GraphData::edgePrefix() noexcept
{
  return m_edgePrefix.get();
}


vtx_type * GraphData::edgeList() noexcept
{
  return m_edgeList.get();
}


wgt_type * GraphData::vertexWeight() noexcept
{
  return m_vertexWeight.get();
}


wgt_type * GraphData::edgeWeight() noexcept
{
  return m_edgeWeight.get();
}


adj_type const * GraphData::edgePrefix() const noexcept
{
  return m_edgePrefix.get();
}


vtx_type const * GraphData::edgeList() const noexcept
{
  return m_edgeList.get();
}


wgt_type const * GraphData::vertexWeight() const noexcept
{
  return m_vertexWeight.get();
}


wgt_type const * GraphData::edgeWeight() const noexcept
{
  return m_edgeWeight.get();
}


}
