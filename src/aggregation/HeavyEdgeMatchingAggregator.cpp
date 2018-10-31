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
#include "graph/DegreeSortedVertexSet.hpp"


#include <iostream>
#include "solidutils/Timer.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


HeavyEdgeMatchingAggregator::HeavyEdgeMatchingAggregator(
    RandomEngineHandle rng) :
  m_rng(rng)
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


Aggregation HeavyEdgeMatchingAggregator::aggregate(
    AggregationParameters const params,
    ConstantGraph const * const graph)
{
  MatchedAggregationBuilder matcher(graph->numVertices());

  sl::Timer tmr;
  tmr.start();

  PermutedVertexSet permutedVertices = \
      DegreeSortedVertexSet::ascendingRandom(graph->vertices(), graph, \
      m_rng.get());

  for (Vertex const vertex : permutedVertices) {
    vtx_type const v = vertex.index;
    if (!matcher.isMatched(v)) {
      // we'll choose our neighbor with the heaviest edge 
      vtx_type max = NULL_VTX;
      wgt_type maxPriority = 0;
      wgt_type const vertexWeight = graph->weightOf(vertex);
      for (Edge const edge : graph->edgesOf(vertex)) {
        Vertex const u = graph->destinationOf(edge);
        wgt_type const coarseWeight = \
            vertexWeight + graph->weightOf(u);
        if (!matcher.isMatched(u.index) && \
            params.isAllowedVertexWeight(coarseWeight)) {
          wgt_type const priority = graph->weightOf(edge);
          if (max == NULL_VTX || maxPriority < priority) {
            maxPriority = priority;
            max = u.index;
          }
        }
      }
      if (max != NULL_VTX) {
        matcher.match(v, max);
      }
    }
  }

  tmr.stop();
  std::cout << "SHEM took " << tmr.poll() << std::endl;

  return matcher.build(graph->getData());
}



}
