/**
* @file RecursiveBisectionPartitioner_test.cpp
* @brief Unit tests for the RecursiveBisectionPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-11
*/


#include "partition/RecursiveBisectionPartitioner.hpp"
#include "partition/RandomFMBisector.hpp"
#include "partition/TargetPartitioning.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/SimpleRandomEngine.hpp"
#include "util/RandomEngineHandle.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{

UNITTEST(RecursiveBisectionPartitioner, ExecuteKWayUniform)
{
  RandomEngineHandle engine(new SimpleRandomEngine(0));

  // create bisector
  RandomFMBisector b(8, engine);

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // generate graph
  GridGraphGenerator gen(10, 6, 5);

  for (pid_type k = 2; k < 10; ++k) {
    ConstantGraph graph = gen.generate();

    TargetPartitioning target(k, graph.getTotalVertexWeight(), \
        0.03);

    // partition 
    Partitioning part = rb.execute(&target, &graph);
    testEqual(part.numPartitions(), k);

    PartitioningAnalyzer analyzer(&part, &target);

    double const imbalance = analyzer.calcMaxImbalance();
    testLess(imbalance, 0.03005) << "Num partitions = " << k;
  }
}

UNITTEST(RecursiveBisectionPartitioner, ExecuteKWay1To5)
{
  RandomEngineHandle engine(new SimpleRandomEngine(0));

  // create bisector
  RandomFMBisector b(8, engine);

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // generate graph
  GridGraphGenerator gen(9, 5, 7);
  gen.setRandomVertexWeight(1,5);

  for (pid_type k = 2; k < 10; ++k) {
    // create partition parameters
    ConstantGraph graph = gen.generate();

    TargetPartitioning target(k, graph.getTotalVertexWeight(), \
        0.03);

    // partition 
    Partitioning part = rb.execute(&target, &graph);
    testEqual(part.numPartitions(), k);

    PartitioningAnalyzer analyzer(&part, &target);

    double const imbalance = analyzer.calcMaxImbalance();
    testLess(imbalance, 0.03005) << "Num partitions = " << k;
  }
}

UNITTEST(RecursiveBisectionPartitioner, Execute4Way)
{
  std::vector<double> targets{0.25, 0.3, 0.3, 0.15};

  RandomEngineHandle engine(new SimpleRandomEngine(0));

  // create bisector
  RandomFMBisector b(8, engine);

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // generate graph
  GridGraphGenerator gen(6, 13, 7);
  gen.setRandomVertexWeight(1, 5);

  ConstantGraph graph = gen.generate();

  TargetPartitioning target(targets.size(), graph.getTotalVertexWeight(), \
      0.03, targets.data());

  // partition 
  Partitioning part = rb.execute(&target, &graph);
  testEqual(part.numPartitions(), targets.size());
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testLess(imbalance, 0.03005);
}

UNITTEST(RecursiveBisectionPartitioner, Execute7Way1To3)
{
  RandomEngineHandle engine(new SimpleRandomEngine(0));

  // create bisector
  RandomBisector b(engine);

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // create partition parameters
  PartitionParameters params(7);
  params.setImbalanceTolerance(0.01);

  // generate graph
  GridGraphGenerator gen(30, 30, 30);
  gen.setRandomVertexWeight(1, 3);

  ConstantGraph graph = gen.generate();
  TargetPartitioning target(7, graph.getTotalVertexWeight(), \
      0.01);

  // partition 
  Partitioning part = rb.execute(&target, &graph);
  testEqual(part.numPartitions(), static_cast<pid_type>(7));
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testLess(imbalance, 0.01005);
}




}
