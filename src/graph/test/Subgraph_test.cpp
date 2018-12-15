/**
* @file Subgraph_test.cpp
* @brief Unit tests for the Subgraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-12
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

#include "graph/Subgraph.hpp"
#include "graph/GraphHandle.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"
#include "solidutils/Array.hpp"
#include "solidutils/VectorMath.hpp"


namespace poros
{


UNITTEST(Subgraph, GetGraph)
{
  GridGraphGenerator gen(5, 5, 5);

  GraphHandle g = gen.generate();

  sl::Array<vtx_type> superMap(g->numVertices());
  sl::VectorMath::increment(superMap.data(), superMap.size(), 1U);

  Subgraph s(g, std::move(superMap));

  testEqual(s.getGraph()->numVertices(), static_cast<vtx_type>(5*5*5));
}


UNITTEST(Subgraph, GetSuperMap)
{
  GridGraphGenerator gen(5, 5, 5);

  GraphHandle g = gen.generate();

  sl::Array<vtx_type> superMap(g->numVertices());
  sl::VectorMath::increment(superMap.data(), superMap.size(), 1U);

  Subgraph s(g, std::move(superMap));

  for (size_t i = 0; i < 5*5*5; ++i) {
    testEqual(s.getSuperMap()[i], static_cast<vtx_type>(i+1));
  }
}


UNITTEST(Subgraph, MapPartitioning)
{
  GridGraphGenerator gen(2,2,1);
  GraphHandle tempG = gen.generate();

  sl::Array<vtx_type> superMap(tempG->numVertices());
  sl::VectorMath::increment(superMap.data(), superMap.size(), 0U);

  Subgraph s(tempG, std::move(superMap));

  Graph const * const g = s.getGraph();

  Partitioning subPart(2, g);
  subPart.assign(Vertex::make(0), 0);
  subPart.assign(Vertex::make(1), 0);
  subPart.assign(Vertex::make(2), 1);
  subPart.assign(Vertex::make(3), 1);

  sl::Array<pid_type> superLabels(g->numVertices());
  s.mapPartitioning(&subPart, superLabels.data(), 3);
  Partitioning superPart(5, g, std::move(superLabels));

  testEqual(superPart.getAssignment(0), static_cast<pid_type>(3));
  testEqual(superPart.getAssignment(1), static_cast<pid_type>(3));
  testEqual(superPart.getAssignment(2), static_cast<pid_type>(4));
  testEqual(superPart.getAssignment(3), static_cast<pid_type>(4));
}


}
