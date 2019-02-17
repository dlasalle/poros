/**
* @file TwoStepGraphBuilder_test.cpp
* @brief Unit tests for the TwoStepGraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-13
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



#include "graph/TwoStepGraphBuilder.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{


UNITTEST(TwoStepGraphBuilder, FullBuild)
{
  // create a ring of 4 vertices
  TwoStepGraphBuilder builder;

  builder.setNumVertices(4);
  builder.beginVertexPhase();

  builder.incVertexNumEdges(0);
  builder.incVertexNumEdges(1);
  builder.incVertexNumEdges(2);
  builder.incVertexNumEdges(3);

  builder.incVertexNumEdges(2);
  builder.incVertexNumEdges(3);
  builder.incVertexNumEdges(1);
  builder.incVertexNumEdges(0);

  builder.setVertexWeight(0, 1);
  builder.setVertexWeight(1, 1);
  builder.setVertexWeight(2, 1);
  builder.setVertexWeight(3, 1);

  builder.beginEdgePhase();

  builder.addEdgeToVertex(0, 1, 2);
  builder.addEdgeToVertex(1, 2, 2);
  builder.addEdgeToVertex(2, 3, 2);
  builder.addEdgeToVertex(3, 0, 2);

  builder.addEdgeToVertex(3, 2, 2);
  builder.addEdgeToVertex(1, 0, 2);
  builder.addEdgeToVertex(0, 3, 2);
  builder.addEdgeToVertex(2, 1, 2);

  GraphHandle graph = builder.finish();

  // verify graph
  testEqual(graph->numVertices(), 4u);
  testEqual(graph->numEdges(), 8u);

  for (Vertex const vertex : graph->vertices()) {
    testEqual(graph->weightOf<false>(vertex), 1u);
    testEqual(graph->degreeOf(vertex), 2u);

    for (Edge const edge : graph->edgesOf(vertex)) {
      testEqual(graph->weightOf<true>(edge), 2u);
    }
  }
}


}
