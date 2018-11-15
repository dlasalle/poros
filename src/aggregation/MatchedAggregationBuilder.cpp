/**
* @file MatchedAggregationBuilder.cpp
* @brief Implementation of the MatchedAggregationBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2018-01-14
*/



#include "MatchedAggregationBuilder.hpp"
#include "solidutils/Array.hpp"


namespace dolos
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

Aggregation MatchedAggregationBuilder::build(
    CSRGraphData const data) const
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

  return Aggregation(std::move(cmap), numCoarseVertices, data);
}



}
