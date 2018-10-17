/**
* @file SubgraphExtractor_test.cpp
* @brief Unit tests for the SubgraphExtractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-12
*/



#include "graph/SubgraphExtractor.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{

UNITTEST(SubgraphExtract, Partitions)
{
  GridGraphGenerator gen(2,2,2);

  ConstantGraph g = gen.generate(); 

  Partitioning p(3, &g);
  p.assignAll(0);
  p.move(Vertex::make(2), 1);
  p.move(Vertex::make(3), 1);
  p.move(Vertex::make(6), 2);
  p.move(Vertex::make(7), 2);

  std::vector<Subgraph> subs = SubgraphExtractor::partitions(&g, &p);

  testEqual(subs[0].getSuperMap(0), 0u);
  testEqual(subs[0].getSuperMap(1), 1u);
  testEqual(subs[0].getSuperMap(2), 4u);
  testEqual(subs[0].getSuperMap(3), 5u);

  testEqual(subs[1].getSuperMap(0), 2u);
  testEqual(subs[1].getSuperMap(1), 3u);
  testEqual(subs[2].getSuperMap(0), 6u);
  testEqual(subs[2].getSuperMap(1), 7u);
}

}
