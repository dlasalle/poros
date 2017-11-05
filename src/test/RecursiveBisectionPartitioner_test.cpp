/**
* @file RecursiveBisectionPartitioner_test.cpp
* @brief Unit tests for the RecursiveBisectionPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-11
*/


#include "solidutils/UnitTest.hpp"
#include "RecursiveBisectionPartitioner.hpp"
#include "RandomBisector.hpp"
#include "TargetPartitioning.hpp"
#include "PartitioningAnalyzer.hpp"
#include "GridGraphGenerator.hpp"


namespace dolos
{

UNITTEST(RandomBisector, ExecuteKWayUniform)
{
  // create bisector
  RandomBisector b;

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // generate graph
  GridGraphGenerator gen(10, 20, 30);

  for (pid_type k = 2; k < 10; ++k) {
    ConstantGraph graph = gen.generate();

    TargetPartitioning target(k, graph.getTotalVertexWeight(), \
        0.03);

    // partition 
    Partitioning part = rb.execute(&target, &graph);
    testEqual(part.getNumPartitions(), k);

    PartitioningAnalyzer analyzer(&part, &target);

    double const imbalance = analyzer.calcMaxImbalance();
    testLess(imbalance, 0.03005);
  }
}

UNITTEST(RandomBisector, ExecuteKWay1To5)
{
  // create bisector
  RandomBisector b;

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // generate graph
  GridGraphGenerator gen(10, 20, 30);
  gen.setRandomVertexWeight(1,5);

  for (pid_type k = 2; k < 10; ++k) {
    // create partition parameters
    ConstantGraph graph = gen.generate();

    TargetPartitioning target(k, graph.getTotalVertexWeight(), \
        0.03);

    // partition 
    Partitioning part = rb.execute(&target, &graph);
    testEqual(part.getNumPartitions(), k);

    PartitioningAnalyzer analyzer(&part, &target);

    // delete me
    std::cout << "Create " << k << " parititions: ";
    for (Partition const & p : part) {
      std::cout << p.getWeight() << "/" << target.getTargetWeight(p.getIndex())
      << "(" << target.getMaxWeight(p.getIndex()) << ") ";
    }
    std::cout << std::endl;

    double const imbalance = analyzer.calcMaxImbalance();
    testLess(imbalance, 0.03005);
  }
}

UNITTEST(RandomBisector, Execute4Way)
{
  std::vector<double> targets{0.25, 0.3, 0.3, 0.15};

  // create bisector
  RandomBisector b;

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // generate graph
  GridGraphGenerator gen(10, 20, 30);
  gen.setRandomVertexWeight(1, 5);

  ConstantGraph graph = gen.generate();

  TargetPartitioning target(targets.size(), graph.getTotalVertexWeight(), \
      0.03, targets.data());

  // partition 
  Partitioning part = rb.execute(&target, &graph);
  testEqual(part.getNumPartitions(), targets.size());
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testLess(imbalance, 0.03005);
}

UNITTEST(RandomBisector, Execute7Way1To3)
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
  TargetPartitioning target(7, graph.getTotalVertexWeight(), \
      0.01);

  // partition 
  Partitioning part = rb.execute(&target, &graph);
  testEqual(part.getNumPartitions(), 7);
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testLess(imbalance, 0.01005);
}




}
