/**
* @file MatchedAggregationBuilder_test.cpp
* @brief Unit tests for the MatchedAggregationBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-23
*/


#include "aggregation/MatchedAggregationBuilder.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{


UNITTEST(MatchedAggregationBuilder, isMatched)
{
  MatchedAggregationBuilder builder(10);

  builder.match(0,5);
  builder.match(2,6);
  builder.match(4,7);

  testTrue(builder.isMatched(0));
  testFalse(builder.isMatched(1));
  testTrue(builder.isMatched(2));
  testFalse(builder.isMatched(3));
  testTrue(builder.isMatched(4));
  testTrue(builder.isMatched(5));
  testTrue(builder.isMatched(6));
  testTrue(builder.isMatched(7));
  testFalse(builder.isMatched(8));
  testFalse(builder.isMatched(9));
}


UNITTEST(MatchedAggregationBuilder, build)
{
  GridGraphGenerator gen(5,2,1);
  ConstantGraph graph = gen.generate();

  MatchedAggregationBuilder builder(graph.numVertices());

  builder.match(0,5);
  builder.match(2,6);
  builder.match(4,7);
  builder.match(1,3);
  builder.match(9,8);

  Aggregation agg = builder.build(graph.getData());

  testEqual(agg.getNumCoarseVertices(), static_cast<vtx_type>(5));

  testEqual(agg.getCoarseVertexNumber(0), agg.getCoarseVertexNumber(5));
  testEqual(agg.getCoarseVertexNumber(2), agg.getCoarseVertexNumber(6));
  testEqual(agg.getCoarseVertexNumber(4), agg.getCoarseVertexNumber(7));
  testEqual(agg.getCoarseVertexNumber(1), agg.getCoarseVertexNumber(3));
  testEqual(agg.getCoarseVertexNumber(9), agg.getCoarseVertexNumber(8));

  testNotEqual(agg.getCoarseVertexNumber(0), agg.getCoarseVertexNumber(2));
  testNotEqual(agg.getCoarseVertexNumber(0), agg.getCoarseVertexNumber(4));
  testNotEqual(agg.getCoarseVertexNumber(0), agg.getCoarseVertexNumber(1));
  testNotEqual(agg.getCoarseVertexNumber(0), agg.getCoarseVertexNumber(9));

  testNotEqual(agg.getCoarseVertexNumber(2), agg.getCoarseVertexNumber(4));
  testNotEqual(agg.getCoarseVertexNumber(2), agg.getCoarseVertexNumber(1));
  testNotEqual(agg.getCoarseVertexNumber(2), agg.getCoarseVertexNumber(9));

  testNotEqual(agg.getCoarseVertexNumber(4), agg.getCoarseVertexNumber(1));
  testNotEqual(agg.getCoarseVertexNumber(4), agg.getCoarseVertexNumber(9));

  testNotEqual(agg.getCoarseVertexNumber(1), agg.getCoarseVertexNumber(9));
}
 
}
