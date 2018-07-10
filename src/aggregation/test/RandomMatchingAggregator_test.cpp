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
#include "util/SimpleRandomEngine.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{


UNITTEST(RandomMatchingAggregator, Aggregate)
{
  GridGraphGenerator gen(30,40,50);
  ConstantGraph graph = gen.generate();

  SimpleRandomEngine rand;

  RandomMatchingAggregator aggregator(&rand);

  Aggregation agg = aggregator.aggregate(&graph);

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
  
}
