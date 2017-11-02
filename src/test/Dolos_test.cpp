/**
* @file Dolos_test.cpp
* @brief Unit tests for the top level API.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-13
*/



#include "DomTest.hpp"
#include "dolos.h"
#include "GridGraphGenerator.hpp"
#include "Partitioning.hpp"
#include "TargetPartitioning.hpp"
#include "PartitioningAnalyzer.hpp"
#include "solidutils/Array.hpp"


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

  Partitioning part(7, &where, &g); 
  TargetPartitioning target(part.getNumPartitions(), \
      g.getTotalVertexWeight(), 0.03);
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();

  testLess(imbalance, 0.03);
  testLessOrEqual(cutEdgeWeight, g.getTotalEdgeWeight());
}


}
