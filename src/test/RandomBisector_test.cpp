/**
* @file RandomBisector_test.cpp
* @brief Unit tests for the RandomBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/


#include <vector>
#include <cstdlib>
#include "DomTest.hpp"
#include "RandomBisector.hpp"
#include "GridGraphGenerator.hpp"
#include "PartitioningAnalyzer.hpp"


namespace dolos
{


UNITTEST(RandomBisector, Execute)
{
  // setup parameters
  BisectionParameters params;
  params.setLeftSideTarget(0.4);
  params.setImbalanceTolerance(0.0);

  // create bisector
  RandomBisector b(&params);

  // generate graph
  GridGraphGenerator gen(40, 40, 1);
  gen.setRandomVertexWeight(1, 5);

  ConstantGraph graph = gen.generate();

  // perform bisection
  Partitioning part = b.execute(graph);

  // verify its balanced
  PartitioningAnalyzer analyzer(graph, part);

  double imbalance = analyzer.getMaxImblance();
  testLessThan(imbalance, 0.001);
}


}
