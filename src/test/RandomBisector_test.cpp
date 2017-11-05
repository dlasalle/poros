/**
* @file RandomBisector_test.cpp
* @brief Unit tests for the RandomBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/


#include "solidutils/UnitTest.hpp"
#include "Partitioning.hpp"
#include "RandomBisector.hpp"
#include "GridGraphGenerator.hpp"
#include "TargetPartitioning.hpp"
#include "PartitioningAnalyzer.hpp"


namespace dolos
{

UNITTEST(RandomBisector, ExecuteUniform)
{
  // create bisector
  RandomBisector b;

  // generate graph
  GridGraphGenerator gen(40, 40, 1);

  ConstantGraph graph = gen.generate();

  // setup parameters
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.0);

  // perform bisection
  Partitioning part = b.execute(&target, &graph);

  std::vector<double> targets{0.5, 0.5};
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testEqual(imbalance, 0.0);
}


UNITTEST(RandomBisector, Execute1To5)
{
  std::vector<double> targets{0.4, 0.6};

  // create bisector
  RandomBisector b;

  // generate graph
  GridGraphGenerator gen(40, 40, 1);
  gen.setRandomVertexWeight(1, 5);

  ConstantGraph graph = gen.generate();

  // setup parameters
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.0, \
      targets.data());

  // perform bisection
  Partitioning part = b.execute(&target, &graph);
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testLess(imbalance, 0.001);
}


}
