/**
* @file PartitioningAnalyzer_test.cpp
* @brief Unit test for the Partitioning analyzer class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-11-03
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



#include "partition/PartitioningAnalyzer.hpp"
#include "partition/TargetPartitioning.hpp"
#include "partition/Partitioning.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"



namespace poros
{


UNITTEST(PartitioningAnalyzer, CalcMaxImbalance)
{
  GridGraphGenerator gen(10, 10, 1);
  Graph graph = gen.generate();

  // create a graph with 30, 20, and 50 balance
  Partitioning part(3, &graph);
  for (vtx_type v = 0; v < graph.numVertices(); ++v) {
    if (v < 30) {
      part.assign(Vertex::make(v), 0);
    } else if (v < 50) {
      part.assign(Vertex::make(v), 1);
    } else {
      part.assign(Vertex::make(v), 2);
    }
  }

  TargetPartitioning target(part.numPartitions(), \
      graph.getTotalVertexWeight(), 0.03);

  PartitioningAnalyzer analyzer(&part, &target);

  // the imbalance should be very nearly 0.5
  testLess(std::abs(analyzer.calcMaxImbalance() - 0.5), 0.001);
}


UNITTEST(PartitioningAnalyzer, GetImbalance)
{
  GridGraphGenerator gen(10, 10, 1);
  Graph graph = gen.generate();

  // create a graph with 30, 20, and 50 balance
  Partitioning part(3, &graph);
  for (vtx_type v = 0; v < graph.numVertices(); ++v) {
    if (v < 30) {
      part.assign(Vertex::make(v), 0);
    } else if (v < 50) {
      part.assign(Vertex::make(v), 1);
    } else {
      part.assign(Vertex::make(v), 2);
    }
  }

  TargetPartitioning target(part.numPartitions(), \
      graph.getTotalVertexWeight(), 0.03);

  PartitioningAnalyzer analyzer(&part, &target);

  // the imbalance should be very nearly -0.1
  testLess(std::abs(analyzer.getImbalance(0) + 0.1), 0.001);
  // the imbalance should be very nearly -0.4
  testLess(std::abs(analyzer.getImbalance(1) + 0.4), 0.001);
  // the imbalance should be very nearly 0.5
  testLess(std::abs(analyzer.getImbalance(2) - 0.5), 0.001);
}

UNITTEST(PartitioningAnalyzer, IsOverWeight)
{
  GridGraphGenerator gen(10, 10, 1);
  Graph graph = gen.generate();

  // create a graph with 30, 20, and 50 balance
  Partitioning part(3, &graph);
  for (vtx_type v = 0; v < graph.numVertices(); ++v) {
    if (v < 30) {
      part.assign(Vertex::make(v), 0);
    } else if (v < 50) {
      part.assign(Vertex::make(v), 1);
    } else {
      part.assign(Vertex::make(v), 2);
    }
  }

  TargetPartitioning target(part.numPartitions(), \
      graph.getTotalVertexWeight(), 0.03);

  PartitioningAnalyzer analyzer(&part, &target);

  testFalse(analyzer.isOverWeight(0));
  testFalse(analyzer.isOverWeight(1));
  testTrue(analyzer.isOverWeight(2));
}

}
