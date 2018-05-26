/**
* @file Dolos_test.cpp
* @brief Unit tests for the top level API.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-13
*/



#include "dolos.h"
#include "partition/Partitioning.hpp"
#include "partition/TargetPartitioning.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "util/GridGraphGenerator.hpp"
#include "solidutils/Array.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{


UNITTEST(Dolos, PartGraphRecursiveSeven)
{
  GridGraphGenerator gen(25, 25, 25);
  gen.setRandomEdgeWeight(1,10);
  gen.setRandomVertexWeight(1,3);

  ConstantGraph g = gen.generate();

  wgt_type cutEdgeWeight;

  sl::Array<pid_type> where(g.getNumVertices());
  int r = DOLOS_PartGraphRecursive(g.getNumVertices(), g.getEdgePrefix(), \
      g.getEdgeList(), g.getVertexWeight(), g.getEdgeWeight(), \
      7, nullptr, &cutEdgeWeight, where.data());

  testEqual(r, 1);

  Partitioning part(7, &g, &where); 
  TargetPartitioning target(part.getNumPartitions(), \
      g.getTotalVertexWeight(), 0.03);
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();

  testLess(imbalance, 0.03);
  testLessOrEqual(cutEdgeWeight, g.getTotalEdgeWeight());
}


}
