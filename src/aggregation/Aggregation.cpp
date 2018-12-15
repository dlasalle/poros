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


namespace poros
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

Aggregation::Aggregation(
    sl::Array<vtx_type> coarseMap,
    vtx_type const numCoarseVertices) :
  m_numFineVertices(coarseMap.size()),
  m_numCoarseVertices(numCoarseVertices),
  m_coarseMap(std::move(coarseMap)),
  m_finePrefix(numCoarseVertices+1, 0),
  m_fineMap(m_numFineVertices)
{
  // build prefix and fine map
  for (vtx_type v = 0; v < m_numFineVertices; ++v) {
    ++m_finePrefix[m_coarseMap[v]+1];
  }
  sl::VectorMath::prefixSumExclusive(m_finePrefix.begin(), m_finePrefix.end());
  for (vtx_type v = 0; v < m_numFineVertices; ++v) {
    vtx_type const vtx = m_coarseMap[v];
    m_fineMap[m_finePrefix[vtx+1]] = v;
    ++m_finePrefix[vtx+1];
  }
}

Aggregation::Aggregation(
    Aggregation && rhs) :
  m_numFineVertices(rhs.m_numFineVertices),
  m_numCoarseVertices(rhs.m_numCoarseVertices),
  m_coarseMap(std::move(rhs.m_coarseMap)),
  m_finePrefix(std::move(rhs.m_finePrefix)),
  m_fineMap(std::move(rhs.m_fineMap))
{
  rhs.m_numCoarseVertices = 0;
}

Aggregation& Aggregation::operator=(
    Aggregation && rhs)
{
  m_numFineVertices = rhs.m_numFineVertices;
  m_numCoarseVertices = rhs.m_numCoarseVertices;
  rhs.m_numCoarseVertices = 0;
  rhs.m_numFineVertices = 0;
  m_coarseMap = std::move(rhs.m_coarseMap);
  m_finePrefix = std::move(rhs.m_finePrefix);
  m_fineMap = std::move(rhs.m_fineMap);

  return *this;
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

VertexGrouping Aggregation::coarseVertices() const noexcept
{
  return VertexGrouping(m_numCoarseVertices, m_finePrefix.data(), \
      m_fineMap.data());
}


void Aggregation::fillCoarseMap(
    vtx_type * data) const noexcept
{
  for (vtx_type v = 0; v < m_numFineVertices; ++v) {
    data[v] = m_coarseMap[v];
  }
}


}
