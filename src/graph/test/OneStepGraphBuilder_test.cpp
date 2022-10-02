/**
* @file OneStepGraphBuilder_test.cpp
* @brief Unit tests for the OneStepGraphBuilder class.
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

#include "graph/OneStepGraphBuilder.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>

namespace poros
{

/******************************************************************************
* UNIT TESTS ******************************************************************
******************************************************************************/

UNITTEST(OneStepGraphBuilderTest, BuildStar)
{
  OneStepGraphBuilder builder(7, 12);

  builder.addEdge(1, 1);
  builder.addEdge(2, 1);
  builder.addEdge(3, 1);
  builder.addEdge(4, 1);
  builder.addEdge(5, 1);
  builder.addEdge(6, 1);
  builder.finishVertex(1);

  builder.addEdge(0, 1);
  builder.finishVertex(1);

  builder.addEdge(0, 1);
  builder.finishVertex(1);

  builder.addEdge(0, 1);
  builder.finishVertex(1);

  builder.addEdge(0, 1);
  builder.finishVertex(1);

  builder.addEdge(0, 1);
  builder.finishVertex(1);

  builder.addEdge(0, 1);
  builder.finishVertex(1);

  GraphHandle g = builder.finish();

  testEqual(g->numVertices(), static_cast<vtx_type>(7));
  testEqual(g->numEdges(), static_cast<vtx_type>(12));

  testEqual(g->degreeOf(Vertex::make(0)), static_cast<vtx_type>(6));
  testEqual(g->degreeOf(Vertex::make(1)), static_cast<vtx_type>(1));
  testEqual(g->degreeOf(Vertex::make(2)), static_cast<vtx_type>(1));
  testEqual(g->degreeOf(Vertex::make(3)), static_cast<vtx_type>(1));
  testEqual(g->degreeOf(Vertex::make(4)), static_cast<vtx_type>(1));
  testEqual(g->degreeOf(Vertex::make(5)), static_cast<vtx_type>(1));
}


}

