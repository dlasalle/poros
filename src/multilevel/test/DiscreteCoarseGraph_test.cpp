/**
* @file DiscreteCoarseGraph_test.cpp
* @brief Unit tests for the DiscreteCoarseGraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-10
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


#include "multilevel/DiscreteCoarseGraph.hpp"
#include "aggregation/Aggregation.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{

UNITTEST(DiscreteCoarseGraph, Contract)
{
  GridGraphGenerator gen(2,8,1);
  GraphHandle graph = gen.generate();

  sl::Array<vtx_type> cmap(graph->numVertices());

  for (vtx_type i = 0; i < graph->numVertices(); ++i) {
    cmap[i] = static_cast<vtx_type>(i/2);
  }

  Aggregation agg(std::move(cmap), 8);

  DiscreteCoarseGraph coarse(graph.get(), &agg);

  Graph const * coarseGraph = coarse.graph();

  // check size
  testEqual(coarseGraph->numVertices(), 8U);
  testEqual(coarseGraph->numEdges(), 14U);
  
  // check edge counts
  testEqual(coarseGraph->degreeOf(Vertex::make(0)), static_cast<vtx_type>(1));
  testEqual(coarseGraph->degreeOf(Vertex::make(1)), static_cast<vtx_type>(2));
  testEqual(coarseGraph->degreeOf(Vertex::make(2)), static_cast<vtx_type>(2));
  testEqual(coarseGraph->degreeOf(Vertex::make(3)), static_cast<vtx_type>(2));
  testEqual(coarseGraph->degreeOf(Vertex::make(4)), static_cast<vtx_type>(2));
  testEqual(coarseGraph->degreeOf(Vertex::make(5)), static_cast<vtx_type>(2));
  testEqual(coarseGraph->degreeOf(Vertex::make(6)), static_cast<vtx_type>(2));
  testEqual(coarseGraph->degreeOf(Vertex::make(7)), static_cast<vtx_type>(1));

  // check edge and vertex weights
  for (Vertex const vertex : coarseGraph->vertices()) {
    testEqual(coarseGraph->weightOf(vertex), static_cast<wgt_type>(2));
    for (Edge const edge : coarseGraph->edgesOf(vertex)) {
      testEqual(coarseGraph->weightOf(edge), static_cast<wgt_type>(2));
      testEqual(std::abs(static_cast<int>(coarseGraph->destinationOf(edge).index)
          - static_cast<int>(vertex.index)), 1);
    }
  }
}

}
