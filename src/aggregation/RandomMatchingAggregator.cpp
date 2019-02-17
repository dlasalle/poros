/**
* @file RandomMatchingAggregator.cpp
* @brief The RandomMatchingAggregator implementation.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
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



#include "RandomMatchingAggregator.hpp"
#include "aggregation/MatchedAggregationBuilder.hpp"
#include "graph/RandomOrderVertexSet.hpp"

namespace poros
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

template<bool HAS_VERTEX_WEIGHTS>
void firstMatch(
    AggregationParameters const params,
    Graph const * const graph,
    PermutedVertexSet const permutedVertices,
    MatchedAggregationBuilder * const matcher)
{
  for (Vertex const vertex : permutedVertices) {
    vtx_type const v = vertex.index;
    if (!matcher->isMatched(v)) {
      // we'll choose our neighbor randomly by finding the one with the highest
      // index in the permutation array
      vtx_type max = NULL_VTX;
      vtx_type const vertexWeight = graph->weightOf<HAS_VERTEX_WEIGHTS>(vertex);
      vtx_type maxPriority = 0;
      for (Edge const edge : graph->edgesOf(vertex)) {
        Vertex const u = graph->destinationOf(edge);
        wgt_type const coarseWeight = \
            vertexWeight + graph->weightOf<HAS_VERTEX_WEIGHTS>(u);
        if (!matcher->isMatched(u.index) && \
            params.isAllowedVertexWeight(coarseWeight)) {
          vtx_type const priority = permutedVertices[u.index].index;
          if (max == NULL_VTX || maxPriority < priority) {
            maxPriority = priority;
            max = u.index;
            break;
          }
        }
      }
      if (max != NULL_VTX) {
        matcher->match(v, max);
      }
    }
  }
}

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
    Graph const * const graph)
{
  MatchedAggregationBuilder matcher(graph->numVertices());

  PermutedVertexSet permutedVertices = RandomOrderVertexSet::generate(
      graph->vertices(), m_rng.get());

  if (graph->hasUnitVertexWeight()) {
    firstMatch<false>(params, graph, std::move(permutedVertices), &matcher);
  } else {
    firstMatch<true>(params, graph, std::move(permutedVertices), &matcher);
  }

  return matcher.build();
}



}
