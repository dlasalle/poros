/**
* @file Partitioning_test.cpp
* @brief Unit tests for the partitioning class. 
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-05
*/

#include "DomTest.hpp"
#include "Partitioning.hpp"
#include "GridGraphGenerator.hpp"


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

  part.move(0, 1);

  double imbalance = part.calcMaxImbalance(targets.data());
  testEqual(imbalance, 0.5);
}



}
