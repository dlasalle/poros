/**
* @file Graph_test.cpp
* @brief Unit tests for the Graph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-11
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


#include <vector>
#include "graph/Graph.hpp"
#include "solidutils/UnitTest.hpp"
#include "solidutils/Timer.hpp"
#include "graph/GridGraphGenerator.hpp"


namespace poros
{


UNITTEST(Graph, IterateVertices)
{
  GridGraphGenerator gen(5, 5, 5);

  Graph g = gen.generate();

  std::vector<bool> visited(g.numVertices(), false);
  for (Vertex const v : g.vertices()) {
    visited[v.index] = true;    
  }

  for (bool const & v : visited) {
    testTrue(v);
  }
}


UNITTEST(Graph, IterateEdges)
{
  GridGraphGenerator gen(5, 5, 5);

  Graph g = gen.generate();

  std::vector<bool> visited(g.numEdges(), false);
  for (Edge const & e : g.edges()) {
    visited[e.index] = true;
  }

  for (bool const & e : visited) {
    testTrue(e);
  }
}


UNITTEST(Graph, IteratePerVertexEdges)
{
  GridGraphGenerator gen(5, 5, 5);

  Graph g = gen.generate();

  std::vector<bool> visited(g.numEdges(), false);
  for (Vertex const v : g.vertices()) {
    for (Edge const e : g.edgesOf(v)) {
      visited[e.index] = true;
    }
  }

  for (bool const & e : visited) {
    testTrue(e);
  }
}


}
