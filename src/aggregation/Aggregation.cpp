/**
* @file Aggregation.cpp
* @brief Implementation of the Aggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-01-15
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
