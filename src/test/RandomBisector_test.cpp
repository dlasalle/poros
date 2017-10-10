/**
* @file RandomBisector_test.cpp
* @brief Unit tests for the RandomBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/


#include "DomTest.hpp"
#include "RandomBisector.hpp"
#include "GridGraphGenerator.hpp"
#include "PartitioningAnalyzer.hpp"


namespace dolos
{


UNITTEST(RandomBisector, Execute)
{
  std::vector<double> targets{0.4, 0.6};

  // setup parameters
  BisectionParameters params;
  params.setTargetFractions(targets.data());
  params.setImbalanceTolerance(0.0);

  // create bisector
  RandomBisector b;

  // generate graph
  GridGraphGenerator gen(40, 40, 1);
  gen.setRandomVertexWeight(1, 5);

  ConstantGraph graph = gen.generate();

  // perform bisection
  Partitioning part = b.execute(&params, &graph);

  // verify its balanced
  PartitioningAnalyzer analyzer(&graph, &part);

  double imbalance = analyzer.calcMaxImbalance(targets.data());
  testLess(imbalance, 0.001);
}


}
