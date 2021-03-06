/**
* @file SummationContractor_test.cpp
* @brief Unit tests for the SummationContractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-01-18
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



#include "aggregation/SummationContractor.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{


/******************************************************************************
* UNIT TESTS ******************************************************************
******************************************************************************/

UNITTEST(SummationContractor, ContractLine)
{
  GridGraphGenerator gen(2,8,1);
  Graph graph = gen.generate();

  sl::Array<vtx_type> cmap(graph.numVertices());

  for (vtx_type i = 0; i < graph.numVertices(); ++i) {
    cmap[i] = static_cast<vtx_type>(i/2);
  }

  Aggregation agg(std::move(cmap), 8u);

  SummationContractor contractor;

  // the coarse graph should just be a line with 8 vertices and every edge
  // should be of weight 2
  GraphHandle out = contractor.contract(&graph, &agg);

  testEqual(out->numVertices(), agg.getNumCoarseVertices());

  testEqual(out->degreeOf(Vertex::make(0)), static_cast<vtx_type>(1));
  testEqual(out->degreeOf(Vertex::make(1)), static_cast<vtx_type>(2));
  testEqual(out->degreeOf(Vertex::make(2)), static_cast<vtx_type>(2));
  testEqual(out->degreeOf(Vertex::make(3)), static_cast<vtx_type>(2));
  testEqual(out->degreeOf(Vertex::make(4)), static_cast<vtx_type>(2));
  testEqual(out->degreeOf(Vertex::make(5)), static_cast<vtx_type>(2));
  testEqual(out->degreeOf(Vertex::make(6)), static_cast<vtx_type>(2));
  testEqual(out->degreeOf(Vertex::make(7)), static_cast<vtx_type>(1));

  for (Edge const & edge : out->edges()) {
    testEqual(out->weightOf<true>(edge), static_cast<wgt_type>(2));
  }
}

UNITTEST(SummationContractor, ContractCubeComplete)
{
  GridGraphGenerator gen(2,2,2);
  gen.setRandomEdgeWeight(10,10);
  Graph graph = gen.generate();

  sl::Array<vtx_type> cmap(graph.numVertices());

  cmap[0] = static_cast<vtx_type>(0);
  cmap[1] = static_cast<vtx_type>(0);

  cmap[2] = static_cast<vtx_type>(1);
  cmap[3] = static_cast<vtx_type>(1);

  cmap[4] = static_cast<vtx_type>(2);
  cmap[6] = static_cast<vtx_type>(2);

  cmap[5] = static_cast<vtx_type>(3);
  cmap[7] = static_cast<vtx_type>(3);

  Aggregation agg(std::move(cmap), 8);

  SummationContractor contractor;

  // the coarse graph should just be a line with 8 vertices and every edge
  // should be of weight 2
  GraphHandle out = contractor.contract(&graph, &agg);

  testEqual(out->numVertices(), agg.getNumCoarseVertices());

  testEqual(out->degreeOf(Vertex::make(0)), static_cast<vtx_type>(3));
  testEqual(out->degreeOf(Vertex::make(1)), static_cast<vtx_type>(3));
  testEqual(out->degreeOf(Vertex::make(2)), static_cast<vtx_type>(3));
  testEqual(out->degreeOf(Vertex::make(3)), static_cast<vtx_type>(3));

  testEqual(out->getTotalEdgeWeight(), static_cast<wgt_type>(160));
}

UNITTEST(SummationContractor, ContractCubeSquare)
{
  GridGraphGenerator gen(2,2,2);
  Graph graph = gen.generate();

  sl::Array<vtx_type> cmap(graph.numVertices());

  cmap[0] = static_cast<vtx_type>(0);
  cmap[1] = static_cast<vtx_type>(0);

  cmap[2] = static_cast<vtx_type>(1);
  cmap[3] = static_cast<vtx_type>(1);

  cmap[4] = static_cast<vtx_type>(2);
  cmap[5] = static_cast<vtx_type>(2);

  cmap[6] = static_cast<vtx_type>(3);
  cmap[7] = static_cast<vtx_type>(3);

  Aggregation agg(std::move(cmap), 8);

  SummationContractor contractor;

  // the coarse graph should just be a line with 8 vertices and every edge
  // should be of weight 2
  GraphHandle out = contractor.contract(&graph, &agg);

  testEqual(out->numVertices(), agg.getNumCoarseVertices());

  testEqual(out->degreeOf(Vertex::make(0)), static_cast<vtx_type>(2));
  testEqual(out->degreeOf(Vertex::make(1)), static_cast<vtx_type>(2));
  testEqual(out->degreeOf(Vertex::make(2)), static_cast<vtx_type>(2));
  testEqual(out->degreeOf(Vertex::make(3)), static_cast<vtx_type>(2));

  testEqual(out->getTotalEdgeWeight(), static_cast<wgt_type>(16));

  for (Edge const & edge : out->edges()) {
    testEqual(out->weightOf<true>(edge), static_cast<wgt_type>(2));
  }
}




}
