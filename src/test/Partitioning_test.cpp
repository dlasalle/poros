/**
* @file Partitioning_test.cpp
* @brief Unit tests for the partitioning class. 
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-05
*/


#include "solidutils/UnitTest.hpp"
#include "Partitioning.hpp"
#include "GridGraphGenerator.hpp"
#include "TargetPartitioning.hpp"
#include "PartitioningAnalyzer.hpp"


namespace dolos
{

UNITTEST(Partitioning, NumberOfPartitions)
{
  GridGraphGenerator gen(9, 7, 5);

  ConstantGraph graph = gen.generate(); 
  Partitioning p(5, &graph);

  testEqual(5, p.getNumPartitions());
}

UNITTEST(Partitioning, CalcMaxImbalance)
{
  std::vector<double> targets{0.5, 0.5};

  // generate graph
  GridGraphGenerator gen(2, 2, 1);

  ConstantGraph graph = gen.generate();

  Partitioning part(2, &graph);

  part.assign(0, 1);
  part.assign(1, 0);
  part.assign(2, 0);
  part.assign(3, 0);

  TargetPartitioning target(targets.size(), graph.getTotalVertexWeight(), \
      0.03);
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testEqual(imbalance, 0.5);
}



}
