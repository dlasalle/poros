/**
* @file RandomBisector_test.cpp
* @brief Unit tests for the RandomBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/


#include "DomTest.hpp"
#include "Partitioning.hpp"
#include "RandomBisector.hpp"
#include "GridGraphGenerator.hpp"
#include "TargetPartitioning.hpp"
#include "PartitioningAnalyzer.hpp"


namespace dolos
{

UNITTEST(RandomBisector, ExecuteUniform)
{
  // setup parameters
  BisectionParameters params;
  params.setImbalanceTolerance(0.0);

  // create bisector
  RandomBisector b;

  // generate graph
  GridGraphGenerator gen(40, 40, 1);

  ConstantGraph graph = gen.generate();

  // perform bisection
  Partitioning part = b.execute(&params, &graph);

  std::vector<double> targets{0.5, 0.5};
  TargetPartitioning target(targets.size(), graph.getTotalVertexWeight(), \
      params.getImbalanceTolerance(), targets.data());
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testEqual(imbalance, 0.0);
}


UNITTEST(RandomBisector, Execute1To5)
{
  std::vector<double> targets{0.4, 0.6};

  // setup parameters
  BisectionParameters params;
  params.setTargetPartitionFractions(targets.data());
  params.setImbalanceTolerance(0.0);

  // create bisector
  RandomBisector b;

  // generate graph
  GridGraphGenerator gen(40, 40, 1);
  gen.setRandomVertexWeight(1, 5);

  ConstantGraph graph = gen.generate();

  // perform bisection
  Partitioning part = b.execute(&params, &graph);
  TargetPartitioning target(targets.size(), graph.getTotalVertexWeight(), \
      params.getImbalanceTolerance(), targets.data());
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testLess(imbalance, 0.001);
}


}
