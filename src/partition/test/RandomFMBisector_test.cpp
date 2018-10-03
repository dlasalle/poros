/**
* @file RandomFMBisector_test.cpp
* @brief Unit tests for RandomFMBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-11-06
*/


#include "partition/RandomFMBisector.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{


UNITTEST(RandomFMBisector, Execute)
{
  GridGraphGenerator gen(5, 5, 5);
  ConstantGraph graph = gen.generate();

  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.1);

  RandomEngineHandle engine = RandomEngineFactory::make(0);

  RandomFMBisector b(8, engine);

  Partitioning part = b.execute(&target, &graph);
  PartitioningAnalyzer analyzer(&part, &target);

  testLessOrEqual(analyzer.calcMaxImbalance(), 0.1005);

  // within a factor 3 of best
  testLessOrEqual(part.getCutEdgeWeight(), 90u);
}

}

