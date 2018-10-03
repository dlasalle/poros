/**
* @file RandomBisector_test.cpp
* @brief Unit tests for the RandomBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-09
*/


#include "partition/Partitioning.hpp"
#include "partition/RandomBisector.hpp"
#include "partition/TargetPartitioning.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{

UNITTEST(RandomBisector, ExecuteUniform)
{
  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  RandomBisector b(engine);

  // generate graph
  GridGraphGenerator gen(40, 40, 1);

  ConstantGraph graph = gen.generate();

  // setup parameters
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.0);

  // perform bisection
  Partitioning part = b.execute(&target, &graph);

  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testEqual(imbalance, 0.0);
}


UNITTEST(RandomBisector, Execute1To5)
{
  std::vector<double> targets{0.4, 0.6};

  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  RandomBisector b(engine);

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


UNITTEST(RandomBisector, ExecuteCut)
{
  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  RandomBisector b(engine);

  // generate graph
  GridGraphGenerator gen(40, 40, 1);

  ConstantGraph graph = gen.generate();

  // setup parameters
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.0);

  // perform bisection
  Partitioning part = b.execute(&target, &graph);

  wgt_type maxCut = graph.getTotalEdgeWeight() / 2;
  wgt_type minCut = 40;

  testLessOrEqual(part.getCutEdgeWeight(), maxCut);
  testGreaterOrEqual(part.getCutEdgeWeight(), minCut);
}


}
