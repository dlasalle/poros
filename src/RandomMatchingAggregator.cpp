/**
* @file RandomMatchingAggregator.cpp
* @brief The RandomMatchingAggregator implementation.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-01-14
*/



#include "RandomMatchingAggregator.hpp"
#include "MatchedAggregationBuilder.hpp"
#include "RandomOrderVertexSet.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


RandomMatchingAggregator::RandomMatchingAggregator()
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
    ConstantGraph const * const graph,
    IRandomEngine * const randomEngine) const
{
  MatchedAggregationBuilder matcher(graph->getNumVertices());

  PermutedVertexSet permutedVertices = RandomOrderVertexSet::generate(graph->getVertices(), randomEngine);

  for (Vertex const & vertex : permutedVertices) {
    vtx_type const v = vertex.index();
    if (!matcher.isMatched(v)) {
      // we'll choose our neighbor randomly by finding the one with the highest
      // index in the permutation array
      vtx_type max = NULL_VTX;
      vtx_type maxPriority = 0;
      for (Edge const & edge : vertex.getEdges()) {
        vtx_type const u = edge.destination();
        if (!matcher.isMatched(u)) {
          vtx_type const priority = permutedVertices[u].index();
          if (max == NULL_VTX || maxPriority < priority) {
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
