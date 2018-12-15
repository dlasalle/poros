/**
* @file HeavyEdgeMatchingAggregator_test.cpp
* @brief Unit tests of the HeavyEdgeMatchingAggregator class.
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

#include "aggregation/HeavyEdgeMatchingAggregator.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{


UNITTEST(HeavyEdgeMatchingAggregator, LimitTwoMatch)
{
  GridGraphGenerator gen(30,40,50);
  Graph graph = gen.generate();

  RandomEngineHandle rand = RandomEngineFactory::make(0);

  HeavyEdgeMatchingAggregator aggregator(rand);

  AggregationParameters params;
  Aggregation agg = aggregator.aggregate(params, &graph);

  testGreaterOrEqual(agg.getNumCoarseVertices(), graph.numVertices() / 2); 
  testLess(agg.getNumCoarseVertices(), \
      static_cast<vtx_type>(graph.numVertices() * 0.6)); 

  // verify at most two vertices per coarse vertex
  std::vector<int> matchCount(agg.getNumCoarseVertices(), 0);
  for (Vertex const & vertex : graph.vertices()) {
    vtx_type const coarse = agg.getCoarseVertexNumber(vertex.index);
    ++matchCount[coarse];
  }

  for (int const count : matchCount) {
    testGreaterOrEqual(count, 1);
    testLessOrEqual(count, 2);
  }
}

UNITTEST(HeavyEdgeMatchingAggregator, ConnectedMatch)
{
  GridGraphGenerator gen(30,40,50);
  Graph graph = gen.generate();

  RandomEngineHandle rand = RandomEngineFactory::make(0);

  HeavyEdgeMatchingAggregator aggregator(rand);

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
      for (Edge const & e : graph.edgesOf(set[0])) {
        if (graph.destinationOf(e) == set[1]) {
          found = true;
          break;
        }
      }
      testTrue(found);
    }
  }
}

UNITTEST(HeavyEdgeMatchingAggregator, MaxSize)
{
  GridGraphGenerator gen(30,40,50);
  Graph graph = gen.generate();

  RandomEngineHandle rand = RandomEngineFactory::make(0);

  HeavyEdgeMatchingAggregator aggregator(rand);

  AggregationParameters params;
  params.setMaxVertexWeight(10);
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
      for (Edge const e : graph.edgesOf(set[0])) {
        if (graph.destinationOf(e) == set[1]) {
          found = true;
          break;
        }
      }
      testTrue(found);
    }
  }
}
  
}
