/**
* @file Partitioning_test.cpp
* @brief Unit tests for the partitioning class. 
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-05
*/


#include "solidutils/UnitTest.hpp"
#include "Partitioning.hpp"
#include "GridGraphGenerator.hpp"
#include "TargetPartitioning.hpp"
#include "PartitioningAnalyzer.hpp"


namespace dolos
{


UNITTEST(Partitioning, BlankConstructor)
{
  GridGraphGenerator gen(9, 7, 5);

  ConstantGraph graph = gen.generate(); 
  Partitioning p(5, &graph);

  for (Vertex const & vertex : graph.getVertices()) {
    vtx_type const v = vertex.getIndex();
    p.assign(v, v % 5);
  }

  // check partition weights -- should all be 9x7
  for (Partition const & part : p) {
    testEqual(part.getWeight(), 9u*7u);
  }
}


UNITTEST(Partitioning, VectorConstructor)
{
  GridGraphGenerator gen(9, 7, 5);
  ConstantGraph graph = gen.generate(); 
  
  sl::Array<pid_type> labels(graph.getNumVertices());
  for (Vertex const & vertex : graph.getVertices()) {
    vtx_type const v = vertex.getIndex();
    labels[v] = v % 5;
  }

  Partitioning p(5, &graph, &labels);

  // check partition weights -- should all be 9x7
  for (Partition const & part : p) {
    testEqual(part.getWeight(), 9u*7u);
  }
}


UNITTEST(Partitioning, MoveConstructor)
{
  GridGraphGenerator gen(9, 7, 5);
  ConstantGraph graph = gen.generate(); 
  
  sl::Array<pid_type> labels(graph.getNumVertices());
  for (Vertex const & vertex : graph.getVertices()) {
    vtx_type const v = vertex.getIndex();
    labels[v] = v % 5;
  }

  Partitioning p1(5, &graph, &labels);
  Partitioning p2(std::move(p1));

  // check partition weights -- should all be 9x7
  for (Partition const & part : p2) {
    testEqual(part.getWeight(), 9u*7u);
  }
}


UNITTEST(Partitioning, NumberOfPartitions)
{
  GridGraphGenerator gen(9, 7, 5);

  ConstantGraph graph = gen.generate(); 
  Partitioning p(5, &graph);

  testEqual(5u, p.getNumPartitions());
}


UNITTEST(Partitioning, CalcVertexCounts)
{
  GridGraphGenerator gen(9, 7, 5);
  ConstantGraph graph = gen.generate(); 
  
  sl::Array<pid_type> labels(graph.getNumVertices());
  for (Vertex const & vertex : graph.getVertices()) {
    vtx_type const v = vertex.getIndex();
    if (v < 15) {
      labels[v] = 0;
    } else if (v < 40) {
      labels[v] = 1;
    } else if (v < 148) {
      labels[v] = 2;
    } else if (v < 160) {
      labels[v] = 3;
    } else {
      labels[v] = 4;
    }
  }

  Partitioning p(5, &graph, &labels);

  std::vector<vtx_type> counts = p.calcVertexCounts();

  // check counts
  for (Partition const & part : p) {
    testEqual(counts[part.getIndex()], part.getWeight());
  }
}


}
