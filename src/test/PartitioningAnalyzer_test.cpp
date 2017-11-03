/**
* @file PartitioningAnalyzer_test.cpp
* @brief Unit test for the Partitioning analyzer class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-11-03
*/



#include "PartitioningAnalyzer.hpp"
#include "GridGraphGenerator.hpp"
#include "TargetPartitioning.hpp"
#include "Partitioning.hpp"
#include "solidutils/UnitTest.hpp"



namespace dolos
{


UNITTEST(PartitioningAnalyzer, CalcMaxImbalance)
{
  GridGraphGenerator gen(10, 10, 1);
  ConstantGraph graph = gen.generate();

  // create a graph with 30, 20, and 50 balance
  Partitioning part(3, &graph);
  for (vtx_type v = 0; v < graph.getNumVertices(); ++v) {
    if (v < 30) {
      part.assign(v, 0);
    } else if (v < 50) {
      part.assign(v, 1);
    } else {
      part.assign(v, 2);
    }
  }

  TargetPartitioning target(part.getNumPartitions(), \
      graph.getTotalVertexWeight(), 0.03);

  PartitioningAnalyzer analyzer(&part, &target);

  // the imbalance should be very nearly 0.515
  testLess(std::abs(analyzer.calcMaxImbalance() - 0.515), 0.001);
}


UNITTEST(PartitioningAnalyzer, GetImbalance)
{
  GridGraphGenerator gen(10, 10, 1);
  ConstantGraph graph = gen.generate();

  // create a graph with 30, 20, and 50 balance
  Partitioning part(3, &graph);
  for (vtx_type v = 0; v < graph.getNumVertices(); ++v) {
    if (v < 30) {
      part.assign(v, 0);
    } else if (v < 50) {
      part.assign(v, 1);
    } else {
      part.assign(v, 2);
    }
  }

  TargetPartitioning target(part.getNumPartitions(), \
      graph.getTotalVertexWeight(), 0.03);

  PartitioningAnalyzer analyzer(&part, &target);

  // the imbalance should be very nearly -0.091
  testLess(std::abs(analyzer.getImbalance(0) + 0.091), 0.001);
  // the imbalance should be very nearly -0.242 
  testLess(std::abs(analyzer.getImbalance(1) + 0.242), 0.001);
  // the imbalance should be very nearly 0.515
  testLess(std::abs(analyzer.getImbalance(2) - 0.515), 0.001);
}

UNITTEST(PartitioningAnalyzer, IsOverWeight)
{
  GridGraphGenerator gen(10, 10, 1);
  ConstantGraph graph = gen.generate();

  // create a graph with 30, 20, and 50 balance
  Partitioning part(3, &graph);
  for (vtx_type v = 0; v < graph.getNumVertices(); ++v) {
    if (v < 30) {
      part.assign(v, 0);
    } else if (v < 50) {
      part.assign(v, 1);
    } else {
      part.assign(v, 2);
    }
  }

  TargetPartitioning target(part.getNumPartitions(), \
      graph.getTotalVertexWeight(), 0.03);

  PartitioningAnalyzer analyzer(&part, &target);

  testFalse(analyzer.isOverWeight(0));
  testFalse(analyzer.isOverWeight(1));
  testTrue(analyzer.isOverWeight(2));
}

}
