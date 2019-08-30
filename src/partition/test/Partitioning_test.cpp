/**
* @file Partitioning_test.cpp
* @brief Unit tests for the partitioning class. 
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-05
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


#include "partition/Partitioning.hpp"
#include "partition/TargetPartitioning.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{


UNITTEST(Partitioning, BlankConstructor)
{
  GridGraphGenerator gen(9, 7, 5);

  Graph graph = gen.generate(); 
  Partitioning p(5, &graph);

  for (Vertex const & vertex : graph.vertices()) {
    vtx_type const v = vertex.index;
    p.assign(Vertex::make(v), v % 5);
  }

  // check partition weights -- should all be 9x7
  for (Partition const & part : p) {
    testEqual(part.weight(), static_cast<wgt_type>(9*7));
  }
}


UNITTEST(Partitioning, VectorConstructor)
{
  GridGraphGenerator gen(9, 7, 5);
  Graph graph = gen.generate(); 
  
  sl::Array<pid_type> labels(graph.numVertices());
  for (Vertex const & vertex : graph.vertices()) {
    vtx_type const v = vertex.index;
    labels[v] = v % 5;
  }

  Partitioning p(5, &graph, std::move(labels));

  // check partition weights -- should all be 9x7
  for (Partition const & part : p) {
    testEqual(part.weight(), static_cast<wgt_type>(9*7));
  }
}


UNITTEST(Partitioning, MoveConstructor)
{
  GridGraphGenerator gen(9, 7, 5);
  Graph graph = gen.generate(); 
  
  sl::Array<pid_type> labels(graph.numVertices());
  for (Vertex const & vertex : graph.vertices()) {
    vtx_type const v = vertex.index;
    labels[v] = v % 5;
  }

  Partitioning p1(5, &graph, std::move(labels));
  Partitioning p2(std::move(p1));

  // check partition weights -- should all be 9x7
  for (Partition const & part : p2) {
    testEqual(part.weight(), static_cast<wgt_type>(9*7));
  }
}


UNITTEST(Partitioning, NumberOfPartitions)
{
  GridGraphGenerator gen(9, 7, 5);

  Graph graph = gen.generate(); 
  Partitioning p(5, &graph);

  testEqual(static_cast<pid_type>(5), p.numPartitions());
}


UNITTEST(Partitioning, CalcVertexCounts)
{
  GridGraphGenerator gen(9, 7, 5);
  Graph graph = gen.generate(); 
  
  sl::Array<pid_type> labels(graph.numVertices());
  for (Vertex const & vertex : graph.vertices()) {
    vtx_type const v = vertex.index;
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

  Partitioning p(5, &graph, std::move(labels));

  std::vector<vtx_type> counts = p.calcVertexCounts();

  // check counts
  for (Partition const & part : p) {
    testEqual(static_cast<wgt_type>(counts[part.index()]), part.weight());
  }
}


}
