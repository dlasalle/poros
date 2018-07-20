/**
* @file HeavyEdgeMatchingAggregation.cpp
* @brief Implementation of the HeavyEdgeMatchingAggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-19
*/


#include "HeavyEdgeMatchingAggregator.hpp"
#include "aggregation/MatchedAggregationBuilder.hpp"
#include "graph/RandomOrderVertexSet.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


HeavyEdgeMatchingAggregator::HeavyEdgeMatchingAggregator(
    IRandomEngine * const rng) :
  m_rng(rng)
{
  // do nothing
}


HeavyEdgeMatchingAggregator::~HeavyEdgeMatchingAggregator()
{
  // do nohting
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


Aggregation HeavyEdgeMatchingAggregator::aggregate(
    ConstantGraph const * const graph) const
{
  MatchedAggregationBuilder matcher(graph->numVertices());

  PermutedVertexSet permutedVertices = RandomOrderVertexSet::generate(
      graph->vertices(), m_rng);

  for (Vertex const & vertex : permutedVertices) {
    vtx_type const v = vertex.index();
    if (!matcher.isMatched(v)) {
      // we'll choose our neighbor with the heaviest edge 
      vtx_type max = NULL_VTX;
      wgt_type maxPriority = 0;
      for (Edge const & edge : vertex.edges()) {
        vtx_type const u = edge.destination();
        if (!matcher.isMatched(u)) {
          wgt_type const priority = edge.weight();
          if (max == NULL_VTX || maxPriority > priority) {
            maxPriority = priority;
            max = u;
          }
        }
      }
      if (max != NULL_VTX) {
        matcher.match(v, max);
      }
    }
  }

  return matcher.build(graph->getData());
}



}
