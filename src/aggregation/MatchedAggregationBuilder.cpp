/**
* @file MatchedAggregationBuilder.cpp
* @brief Implementation of the MatchedAggregationBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2018-01-14
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



#include "MatchedAggregationBuilder.hpp"
#include "solidutils/Array.hpp"


namespace poros
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

MatchedAggregationBuilder::MatchedAggregationBuilder(
    vtx_type const numVertices) :
  m_nextUnmatched(0),
  m_match(numVertices, NULL_VTX)
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Aggregation MatchedAggregationBuilder::build() const
{
  sl::Array<vtx_type> cmap(m_match.size());
  
  vtx_type numCoarseVertices = 0;
  for (vtx_type v = 0; v < m_match.size(); ++v) {
    vtx_type const u = m_match[v];
    if (u == NULL_VTX) {
      // set cmap for unmatched vertices
      cmap[v] = numCoarseVertices;
      ++numCoarseVertices;
    } else if (v < u) {
      // set cmap for matched vertices
      cmap[u] = cmap[v] = numCoarseVertices;
      ++numCoarseVertices;
    }
  }

  return Aggregation(std::move(cmap), numCoarseVertices);
}



}
