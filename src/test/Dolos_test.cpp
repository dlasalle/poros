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


namespace dolos
{


UNITTEST(Dolos, PartGraphRecursiveSeven)
{
  GridGraphGenerator gen(25, 25, 25);
  gen.setRandomEdgeWeight(1,10);
  gen.setRandomVertexWeight(1,3);

  ConstantGraph g = gen.generate();

  wgt_type cutEdgeWeight;

  Partitioning part(7, &g); 

  std::vector<pid_type> where(g.getNumVertices());
  int r = DOLOS_PartGraphRecursive(g.getNumVertices(), g.getEdgePrefix(), \
      g.getEdgeList(), g.getVertexWeight(), g.getEdgeWeight(), \
      part.getNumPartitions(), nullptr, &cutEdgeWeight, where.data());

  testEqual(r, 1);

  for (size_t v = 0; v < where.size(); ++v) {
    part.move(v, where[v]);
  }
}


}