/**
* @file RandomFMBisector_test.cpp
* @brief Unit tests for RandomFMBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-11-06
*/


#include "solidutils/UnitTest.hpp"
#include "RandomFMBisector.hpp"
#include "GridGraphGenerator.hpp"
#include "PartitioningAnalyzer.hpp"


namespace dolos
{


UNITTEST(RandomFMBisector, Execute)
{
  GridGraphGenerator gen(5, 5, 5);
  ConstantGraph graph = gen.generate();

  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.1);

  RandomFMBisector b(8);

  Partitioning part = b.execute(&target, &graph);
  PartitioningAnalyzer analyzer(&part, &target);

  testLessOrEqual(analyzer.calcMaxImbalance(), 0.1005);

  // within a factor 3 of best
  testLessOrEqual(part.getCutEdgeWeight(), 90u);
}

}

