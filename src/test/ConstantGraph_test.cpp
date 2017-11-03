/**
* @file ConstantGraph_test.cpp
* @brief Unit tests for the ConstantGraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-11
*/


#include <vector>
#include "ConstantGraph.hpp"
#include "solidutils/UnitTest.hpp"
#include "GridGraphGenerator.hpp"


namespace dolos
{


UNITTEST(ConstantGraph, IterateVertices)
{
  GridGraphGenerator gen(5, 5, 5);

  ConstantGraph g = gen.generate();

  std::vector<bool> visited(g.getNumVertices(), false);
  for (Vertex const v : g.getVertices()) {
    visited[v.getIndex()] = true;    
  }

  for (bool const & v : visited) {
    testTrue(v);
  }
}


UNITTEST(ConstantGraph, IterateEdges)
{
  GridGraphGenerator gen(5, 5, 5);

  ConstantGraph g = gen.generate();

  std::vector<bool> visited(g.getNumEdges(), false);
  for (Edge const & e : g.getEdges()) {
    visited[e.getIndex()] = true;
  }

  for (bool const & e : visited) {
    testTrue(e);
  }
}


UNITTEST(ConstantGraph, IteratePerVertexEdges)
{
  GridGraphGenerator gen(5, 5, 5);

  ConstantGraph g = gen.generate();

  std::vector<bool> visited(g.getNumEdges(), false);
  for (Vertex const & v : g.getVertices()) {
    for (Edge const & e : v.getEdges()) {
      visited[e.getIndex()] = true;
    }
  }

  for (bool const & e : visited) {
    testTrue(e);
  }
}






}
