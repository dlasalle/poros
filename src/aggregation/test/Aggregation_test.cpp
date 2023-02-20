/**
* @file Aggregation_test.cpp
* @brief Unit tests for the Aggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-24
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

#include "aggregation/Aggregation.hpp"
#include "solidutils/UnitTest.hpp"

namespace poros
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
    for (const Vertex& v : group) {
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
