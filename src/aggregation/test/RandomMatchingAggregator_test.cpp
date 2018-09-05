/**
* @file RandomMatchingAggregator_test.cpp
* @brief Unit tests for the RandomMatchingAggregator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-01-15
*/


#include "aggregation/RandomMatchingAggregator.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{


UNITTEST(RandomMatchingAggregator, LimitTwoMatch)
{
  GridGraphGenerator gen(30,40,50);
  ConstantGraph graph = gen.generate();

  RandomEngineHandle rand = RandomEngineFactory::make(0);

  RandomMatchingAggregator aggregator(rand);

  AggregationParameters params;

  Aggregation agg = aggregator.aggregate(params, &graph);

  testGreaterOrEqual(agg.getNumCoarseVertices(), graph.numVertices() / 2); 
  testLess(agg.getNumCoarseVertices(), \
      static_cast<vtx_type>(graph.numVertices() * 0.6)); 

  // verify at most two vertices per coarse vertex
  std::vector<int> matchCount(agg.getNumCoarseVertices(), 0);
  for (Vertex const & vertex : graph.vertices()) {
    vtx_type const coarse = agg.getCoarseVertexNumber(vertex.index());
    ++matchCount[coarse];
  }

  for (int const count : matchCount) {
    testGreaterOrEqual(count, 1);
    testLessOrEqual(count, 2);
  }

}

UNITTEST(RandomMatchingAggregator, ConnectedMatch)
{
  GridGraphGenerator gen(30,40,50);
  ConstantGraph graph = gen.generate();

  RandomEngineHandle rand = RandomEngineFactory::make(0);

  RandomMatchingAggregator aggregator(rand);

  AggregationParameters params;
  Aggregation agg = aggregator.aggregate(params, &graph);

  testGreaterOrEqual(agg.getNumCoarseVertices(), graph.numVertices() / 2); 
  testLess(agg.getNumCoarseVertices(), \
      static_cast<vtx_type>(graph.numVertices() * 0.6)); 

  // verify at most two vertices per coarse vertex
  std::vector<int> matchCount(agg.getNumCoarseVertices(), 0);
  for (VertexGroup const & group : agg.coarseVertices()) {
    // should be a matching
    testLessOrEqual(group.size(), 2U);
    if (group.size() == 2) {
      PermutedVertexSet const set = group.fineVertices();
      bool found = false;
      for (Edge const & e : set[0].edges()) {
        if (e.destination() == set[1].index()) {
          found = true;
          break;
        }
      }
      testTrue(found);
    }
  }
}
  
}
