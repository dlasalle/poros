/**
* @file MatchedAggregationBuilder_test.cpp
* @brief Unit tests for the MatchedAggregationBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-23
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


#include "aggregation/MatchedAggregationBuilder.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
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
  Graph graph = gen.generate();

  MatchedAggregationBuilder builder(graph.numVertices());

  builder.match(0,5);
  builder.match(2,6);
  builder.match(4,7);
  builder.match(1,3);
  builder.match(9,8);

  Aggregation agg = builder.build();

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
