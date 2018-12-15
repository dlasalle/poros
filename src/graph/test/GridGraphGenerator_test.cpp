/**
* @file GridGraphGenerator_test.cpp
* @brief Unit tests for the GridGraphGenerator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-10
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


#include "graph/GridGraphGenerator.hpp"
#include "graph/Graph.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{


UNITTEST(RandomBisector, Execute)
{
  // generate graph
  GridGraphGenerator gen(17, 10, 3);
  gen.setRandomVertexWeight(1, 3);

  Graph graph = gen.generate();

  testEqual(graph.numVertices(), static_cast<vtx_type>(17*10*3));

  wgt_type const * const vertexWeight = graph.getVertexWeight();
  for (vtx_type v = 0; v < graph.numVertices(); ++v) {
    testGreaterOrEqual(vertexWeight[v], static_cast<wgt_type>(1));
    testLessOrEqual(vertexWeight[v], static_cast<wgt_type>(3));
  }
}


}
