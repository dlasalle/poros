/**
* @file SubgraphExtractor_test.cpp
* @brief Unit tests for the SubgraphExtractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-12
*/



#include "solidutils/UnitTest.hpp"
#include "SubgraphExtractor.hpp"
#include "GridGraphGenerator.hpp"


namespace dolos
{

UNITTEST(SubgraphExtract, Partitions)
{
  GridGraphGenerator gen(2,2,2);

  ConstantGraph g = gen.generate(); 

  Partitioning p(3, &g);
  p.assignAll(0);
  p.move(2, 1);
  p.move(3, 1);
  p.move(6, 2);
  p.move(7, 2);

  std::vector<Subgraph> subs = SubgraphExtractor::partitions(&g, &p);

  testEqual(subs[0].getSuperMap(0), 0);
  testEqual(subs[0].getSuperMap(1), 1);
  testEqual(subs[0].getSuperMap(2), 4);
  testEqual(subs[0].getSuperMap(3), 5);

  testEqual(subs[1].getSuperMap(0), 2);
  testEqual(subs[1].getSuperMap(1), 3);
  testEqual(subs[2].getSuperMap(0), 6);
  testEqual(subs[2].getSuperMap(1), 7);
}

}
