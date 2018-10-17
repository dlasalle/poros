/**
* @file ConstantGraph_test.cpp
* @brief Unit tests for the ConstantGraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-11
*/


#include <vector>
#include "graph/ConstantGraph.hpp"
#include "solidutils/UnitTest.hpp"
#include "solidutils/Timer.hpp"
#include "graph/GridGraphGenerator.hpp"


namespace dolos
{


UNITTEST(ConstantGraph, IterateVertices)
{
  GridGraphGenerator gen(5, 5, 5);

  ConstantGraph g = gen.generate();

  std::vector<bool> visited(g.numVertices(), false);
  for (Vertex const v : g.vertices()) {
    visited[v.index] = true;    
  }

  for (bool const & v : visited) {
    testTrue(v);
  }
}


UNITTEST(ConstantGraph, IterateEdges)
{
  GridGraphGenerator gen(5, 5, 5);

  ConstantGraph g = gen.generate();

  std::vector<bool> visited(g.numEdges(), false);
  for (Edge const & e : g.edges()) {
    visited[e.index] = true;
  }

  for (bool const & e : visited) {
    testTrue(e);
  }
}


UNITTEST(ConstantGraph, IteratePerVertexEdges)
{
  GridGraphGenerator gen(5, 5, 5);

  ConstantGraph g = gen.generate();

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
