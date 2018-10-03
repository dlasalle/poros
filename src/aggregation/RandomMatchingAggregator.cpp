/**
* @file RandomMatchingAggregator.cpp
* @brief The RandomMatchingAggregator implementation.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-01-14
*/



#include "RandomMatchingAggregator.hpp"
#include "aggregation/MatchedAggregationBuilder.hpp"
#include "graph/RandomOrderVertexSet.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


RandomMatchingAggregator::RandomMatchingAggregator(
    RandomEngineHandle rng) :
  m_rng(rng)
{
  // do nothing
}


RandomMatchingAggregator::~RandomMatchingAggregator()
{
  // do nohting
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


Aggregation RandomMatchingAggregator::aggregate(
    AggregationParameters const params,
    ConstantGraph const * const graph)
{
  MatchedAggregationBuilder matcher(graph->numVertices());

  PermutedVertexSet permutedVertices = RandomOrderVertexSet::generate(
      graph->vertices(), m_rng.get());

  for (Vertex const & vertex : permutedVertices) {
    vtx_type const v = vertex.index();
    if (!matcher.isMatched(v)) {
      // we'll choose our neighbor randomly by finding the one with the highest
      // index in the permutation array
      vtx_type max = NULL_VTX;
      vtx_type maxPriority = 0;
      for (Edge const & edge : vertex.edges()) {
        vtx_type const u = edge.destination();
        wgt_type const coarseWeight = \
            vertex.weight() + graph->getVertexWeight(u);
        if (!matcher.isMatched(u) && \
            params.isAllowedVertexWeight(coarseWeight)) {
          vtx_type const priority = permutedVertices[u].index();
          if (max == NULL_VTX || maxPriority < priority) {
            maxPriority = priority;
            max = u;
            break;
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
