/**
* @file HeavyEdgeMatchingAggregation.cpp
* @brief Implementation of the HeavyEdgeMatchingAggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-19
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


#include "HeavyEdgeMatchingAggregator.hpp"
#include "aggregation/MatchedAggregationBuilder.hpp"
#include "graph/DegreeSortedVertexSet.hpp"


namespace poros
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/


namespace
{

template<bool HAS_VERTEX_WEIGHTS, bool HAS_EDGE_WEIGHTS = true>
void shem(
    AggregationParameters const params,
    Graph const * const graph,
    PermutedVertexSet const permutedVertices,
    MatchedAggregationBuilder * const matcher)
{
  for (Vertex const vertex : permutedVertices) {
    vtx_type const v = vertex.index;
    if (!matcher->isMatched(v)) {
      // we'll choose our neighbor with the heaviest edge 
      vtx_type max = NULL_VTX;
      wgt_type maxPriority = 0;
      wgt_type const vertexWeight = graph->weightOf<HAS_VERTEX_WEIGHTS>(vertex);
      for (Edge const edge : graph->edgesOf(vertex)) {
        Vertex const u = graph->destinationOf(edge);
        wgt_type const coarseWeight = \
            vertexWeight + graph->weightOf<HAS_VERTEX_WEIGHTS>(u);
        if (!matcher->isMatched(u.index) && \
            params.isAllowedVertexWeight(coarseWeight)) {
          wgt_type const priority = graph->weightOf<HAS_EDGE_WEIGHTS>(edge);
          if (max == NULL_VTX || maxPriority < priority) {
            maxPriority = priority;
            max = u.index;
          }
        }
      }
      if (max != NULL_VTX) {
        matcher->match(v, max);
      }
    }
  }
}

}



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
    Graph const * const graph)
{
  MatchedAggregationBuilder matcher(graph->numVertices());

  PermutedVertexSet permutedVertices = \
      DegreeSortedVertexSet::ascendingRandom(graph->vertices(), graph, \
      m_rng.get());

  if (graph->hasUnitVertexWeight()) {
    shem<false>(params, graph, std::move(permutedVertices), &matcher);
  } else {
    shem<true>(params, graph, std::move(permutedVertices), &matcher);
  }

  return matcher.build();
}



}
