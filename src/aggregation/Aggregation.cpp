/**
* @file Aggregation.cpp
* @brief Implementation of the Aggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-01-15
*/


#include "Aggregation.hpp"
#include "solidutils/VectorMath.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

Aggregation::Aggregation(
    std::vector<vtx_type> && coarseMap,
    vtx_type const numCoarseVertices,
    CSRGraphData const data) :
  m_numCoarseVertices(numCoarseVertices),
  m_coarseMap(coarseMap),
  m_finePrefix(numCoarseVertices+1, 0),
  m_fineMap(m_coarseMap.size()),
  m_data(data)
{
  // build prefix and fine map
  for (vtx_type const vtx : coarseMap) {
    ++m_finePrefix[vtx+1];
  }
  sl::VectorMath::prefixSumExclusive(m_finePrefix.data(), m_finePrefix.size());
  for (vtx_type v = 0; v < coarseMap.size(); ++v) {
    vtx_type const vtx = coarseMap[v];
    m_fineMap[m_finePrefix[vtx+1]] = v;
    ++m_finePrefix[vtx+1];
  }

  ASSERT_EQUAL(m_finePrefix.back(), m_coarseMap.size());
}

Aggregation::Aggregation(
    Aggregation const & rhs) :
  m_numCoarseVertices(rhs.m_numCoarseVertices),
  m_coarseMap(rhs.m_coarseMap),
  m_finePrefix(rhs.m_finePrefix),
  m_fineMap(rhs.m_fineMap),
  m_data(rhs.m_data)
{
  // do nothing 
}

Aggregation::Aggregation(
    Aggregation && rhs) :
  m_numCoarseVertices(rhs.m_numCoarseVertices),
  m_coarseMap(std::move(rhs.m_coarseMap)),
  m_finePrefix(std::move(rhs.m_finePrefix)),
  m_fineMap(std::move(rhs.m_fineMap)),
  m_data(rhs.m_data)
{
  // do nothing
}

Aggregation& Aggregation::operator=(
    Aggregation const & rhs)
{
  m_numCoarseVertices = rhs.m_numCoarseVertices;
  m_coarseMap = rhs.m_coarseMap;
  m_finePrefix = rhs.m_finePrefix;
  m_fineMap = rhs.m_fineMap;
  m_data = rhs.m_data;

  return *this;
}

Aggregation& Aggregation::operator=(
    Aggregation && rhs)
{
  m_numCoarseVertices = rhs.m_numCoarseVertices;
  rhs.m_numCoarseVertices = 0;
  m_coarseMap = std::move(rhs.m_coarseMap);
  m_finePrefix = std::move(rhs.m_finePrefix);
  m_fineMap = std::move(rhs.m_fineMap);
  m_data = rhs.m_data;

  return *this;
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

VertexGrouping Aggregation::coarseVertices() const noexcept
{
  return VertexGrouping(m_numCoarseVertices, m_finePrefix.data(),
      m_fineMap.data());
}


void Aggregation::fillCoarseMap(
    vtx_type * data) const noexcept
{
  for (vtx_type v = 0; v < m_coarseMap.size(); ++v) {
    data[v] = m_coarseMap[v];
  }
}


}
