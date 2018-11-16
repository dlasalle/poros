/**
* @file MultiBisector_test.cpp
* @brief Unit tests for the MultiBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-20
*/


#include "partition/MultiBisector.hpp"
#include "partition/RandomBisector.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{

UNITTEST(MultiBisector, ExecuteUniform)
{
  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  std::unique_ptr<IBisector> b(new RandomBisector(engine));
  MultiBisector mb(10, std::move(b));

  // generate graph
  GridGraphGenerator gen(40, 40, 1);

  Graph graph = gen.generate();

  // setup parameters
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.0);

  // perform bisection
  Partitioning part = mb.execute(&target, &graph);

  // ensure its balanced
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testEqual(imbalance, 0.0);

  // make 10 random bisections and expect the result to be better than average
  wgt_type cutEdges = 0;
  b.reset(new RandomBisector(engine));
  for (int i = 0; i < 10; ++i) {
    Partitioning testPart = b->execute(&target, &graph);
    
    cutEdges += testPart.getCutEdgeWeight();
  }
  cutEdges /= 10;

  testLess(part.getCutEdgeWeight(), cutEdges);
}
  
}
