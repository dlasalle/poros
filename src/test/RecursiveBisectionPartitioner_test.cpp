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
    // create partition parameters
    PartitionParameters params(k);
    params.setImbalanceTolerance(0.03);

    ConstantGraph graph = gen.generate();

    // partition 
    Partitioning part = rb.execute(&params, &graph);
    testEqual(part.getNumPartitions(), k);

    double imbalance = \
        part.calcMaxImbalance(params.getTargetPartitionFractions());
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
    PartitionParameters params(k);
    params.setImbalanceTolerance(0.03);

    ConstantGraph graph = gen.generate();

    // partition 
    Partitioning part = rb.execute(&params, &graph);
    testEqual(part.getNumPartitions(), k);

    double imbalance = \
        part.calcMaxImbalance(params.getTargetPartitionFractions());
    testLess(imbalance, 0.03);
  }
}

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

  double imbalance = \
      part.calcMaxImbalance(params.getTargetPartitionFractions());
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

  double imbalance = \
      part.calcMaxImbalance(params.getTargetPartitionFractions());
  testLess(imbalance, 0.01);
}




}
