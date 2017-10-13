/**
* @file RecursiveBisectionPartitioner_test.cpp
* @brief Unit tests for the RecursiveBisectionPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-11
*/


#include "DomTest.hpp"
#include "RecursiveBisectionPartitioner.hpp"
#include "RandomBisector.hpp"
#include "PartitionParameters.hpp"
#include "GridGraphGenerator.hpp"
#include "PartitioningAnalyzer.hpp"


namespace dolos
{


UNITTEST(RandomBisector, Execute4Way)
{
  std::vector<double> targets{0.25, 0.3, 0.3, 0.15};

  // create bisector
  RandomBisector b;

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // create partition parameters
  PartitionParameters params(targets.size());
  params.setTargetPartitionFractions(targets.data());
  params.setImbalanceTolerance(0.03);

  // generate graph
  GridGraphGenerator gen(10, 20, 30);
  gen.setRandomVertexWeight(1, 5);

  ConstantGraph graph = gen.generate();

  // partition 
  Partitioning part = rb.execute(&params, &graph);
  testEqual(part.getNumPartitions(), targets.size());

  // verify its balanced
  PartitioningAnalyzer analyzer(&graph, &part);

  double imbalance = \
      analyzer.calcMaxImbalance(params.getTargetPartitionFractions());
  testLess(imbalance, 0.03);
}

UNITTEST(RandomBisector, Execute7WayEven)
{
  // create bisector
  RandomBisector b;

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // create partition parameters
  PartitionParameters params(7);
  params.setImbalanceTolerance(0.01);

  // generate graph
  GridGraphGenerator gen(30, 30, 30);
  gen.setRandomVertexWeight(1, 3);

  ConstantGraph graph = gen.generate();

  // partition 
  Partitioning part = rb.execute(&params, &graph);
  testEqual(part.getNumPartitions(), 7);

  // verify its balanced
  PartitioningAnalyzer analyzer(&graph, &part);

  double imbalance = \
      analyzer.calcMaxImbalance(params.getTargetPartitionFractions());
  testLess(imbalance, 0.01);
}




}
