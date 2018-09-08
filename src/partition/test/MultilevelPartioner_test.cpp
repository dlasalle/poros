/**
* @file MultilevelPartioner_test.cpp
* @brief Unit tests for the MultilevelPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-04
*/


#include "partition/MultilevelPartitioner.hpp"
#include "aggregation/RandomMatchingAggregator.hpp"
#include "partition/BFSBisector.hpp"
#include "partition/RecursiveBisectionPartitioner.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"

#include "solidutils/UnitTest.hpp"

namespace dolos
{


UNITTEST(MultilevelPartitioner, ExecuteFullCoarsen8Part)
{
  // build a grid graph
  GridGraphGenerator gen(8, 8, 8);

  RandomEngineHandle engine = RandomEngineFactory::make(0);

  RandomMatchingAggregator rm(engine);

  BFSBisector bfs(engine);
  RecursiveBisectionPartitioner rb(&bfs);

  // TODO: setup the multilevel partition to contract to 8 coarse vertices
}

}
