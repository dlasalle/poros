/**
* @file RandomOrderVertexSet_test.cpp
* @brief Unit tests for the RandomOrderVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2018-01-14
*/



#include "graph/RandomOrderVertexSet.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>


namespace dolos
{

UNITTEST(RandomOrderVertexSet, Size)
{
  VertexSet vSet(0, 10);

  RandomEngineHandle random = RandomEngineFactory::make(0);

  PermutedVertexSet set = RandomOrderVertexSet::generate(
      vSet, random.get());

  testEqual(set.size(), 10U);
}


UNITTEST(RandomOrderVertexSet, Iterator)
{
  VertexSet vSet(0, 10);

  RandomEngineHandle random = RandomEngineFactory::make(0);

  PermutedVertexSet set = RandomOrderVertexSet::generate(
      vSet, random.get());

  std::vector<bool> marker(vSet.size(), false);

  for (Vertex const vertex : set) {
    marker[vertex.index] = true;
  }

  for (bool mark : marker) {
    testTrue(mark);
  }
}

}
