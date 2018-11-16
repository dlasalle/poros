/**
* @file Aggregation_test.cpp
* @brief Unit tests for the Aggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-24
*/

#include "aggregation/Aggregation.hpp"
#include "solidutils/UnitTest.hpp"

namespace dolos
{

/******************************************************************************
* UNIT TESTS ******************************************************************
******************************************************************************/

UNITTEST(AggregationTest, CoarseVertexNumberTest)
{
  sl::Array<vtx_type> cmap(5);
  cmap[0] = 0;
  cmap[1] = 1;
  cmap[2] = 2;
  cmap[3] = 1;
  cmap[4] = 0;

  Aggregation agg(std::move(cmap), 3u);

  testEqual(agg.getNumCoarseVertices(), 3u);
  testEqual(agg.getCoarseVertexNumber(0), 0u);
  testEqual(agg.getCoarseVertexNumber(1), 1u);
  testEqual(agg.getCoarseVertexNumber(2), 2u);
  testEqual(agg.getCoarseVertexNumber(3), 1u);
  testEqual(agg.getCoarseVertexNumber(4), 0u);
}

UNITTEST(AggregationTest, CoarseVertexSetTest)
{
  sl::Array<vtx_type> cmap(5);
  cmap[0] = 0;
  cmap[1] = 1;
  cmap[2] = 2;
  cmap[3] = 1;
  cmap[4] = 0;
  Aggregation agg(std::move(cmap), 3u);

  testEqual(agg.getNumCoarseVertices(), 3u);

  vtx_type coarse = 0;
  std::vector<bool> visited(5u, false);
  for (const VertexGroup& group : agg.coarseVertices()) {
    for (const Vertex& v : group.fineVertices()) {
      testEqual(agg.getCoarseVertexNumber(v.index), coarse);
      visited[v.index] = true;
    }
    ++coarse;
  }

  for (size_t i = 0; i < visited.size(); ++i) {
    testEqual(visited[i], true) << i;
  }
}

}
