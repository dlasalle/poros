/**
* @file VertexSet_test.cpp
* @brief Unit tests for the VertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2018-01-14
*/



#include "graph/VertexSet.hpp"
#include "solidutils/UnitTest.hpp"

#include <vector>



namespace dolos
{

UNITTEST(VertexSet, Size)
{
  VertexSet set(0, 10);

  testEqual(set.size(), 10U);
}


UNITTEST(VertexSet, Iterator)
{
  VertexSet set(0, 10);

  vtx_type v = 0;
  for (Vertex const & vertex : set) {
    testEqual(vertex.index, v);
    ++v; 
  }
}

}
