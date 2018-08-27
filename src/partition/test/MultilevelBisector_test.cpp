/**
* @file MultilevelBisector_test.cpp
* @brief Unit tests for the MultilevelBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-16
*/


#include "partition/MultilevelBisector.hpp"
#include "aggregation/RandomMatchingAggregator.hpp"
#include "partition/BFSBisector.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "partition/FMRefiner.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/SimpleRandomEngine.hpp"
#include "util/RandomEngineHandle.hpp"

#include "solidutils/UnitTest.hpp"

namespace dolos
{


UNITTEST(MultilevelBisector, ExecuteFullCoarsen8Part)
{
  // build a grid graph
  GridGraphGenerator gen(40, 40, 1);

  ConstantGraph graph = gen.generate();

  // builder our ml bisector
  RandomEngineHandle engine(new SimpleRandomEngine(0));

  std::unique_ptr<IAggregator> agg(new RandomMatchingAggregator(engine));
  std::unique_ptr<IBisector> bis(new BFSBisector(engine));
  std::unique_ptr<ITwoWayRefiner> ref(new FMRefiner(8));

  MultilevelBisector mb(std::move(agg), std::move(bis), std::move(ref));

  // set target partitioning
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.005);

  Partitioning part = mb.execute(&target, &graph);

  wgt_type const maxCut = 80;
  wgt_type const minCut = 40;

  PartitioningAnalyzer analyzer(&part, &target);

  testLessOrEqual(part.getCutEdgeWeight(), maxCut);
  testGreaterOrEqual(part.getCutEdgeWeight(), minCut);

  // balanced to within 0.51%
  testLess(analyzer.calcMaxImbalance(), 0.0051);
}

}
