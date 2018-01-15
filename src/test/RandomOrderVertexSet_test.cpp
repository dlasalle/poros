/**
* @file RandomOrderVertexSet_test.cpp
* @brief Unit tests for the RandomOrderVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2018-01-14
*/



#include "RandomOrderVertexSet.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>


namespace dolos
{

UNITTEST(RandomOrderVertexSet, Size)
{
  std::vector<wgt_type> weight(10, 1);
  std::vector<adj_type> edgePrefix{0,1,2,3,4,5,6,7,8,9,10};;
  std::vector<vtx_type> edgeList{0,1,2,3,4,5,6,7,8,9};
  std::vector<wgt_type> edgeWeight(10, 1);

  RandomOrderVertexSet set(0, 10, weight.data(), edgePrefix.data(), \
      edgeList.data(), edgeWeight.data());

  testEqual(set.size(), 10U);
}


UNITTEST(RandomOrderVertexSet, Iterator)
{
  std::vector<wgt_type> weight(10, 1);
  std::vector<adj_type> edgePrefix{0,1,2,3,4,5,6,7,8,9,10};;
  std::vector<vtx_type> edgeList{0,1,2,3,4,5,6,7,8,9};
  std::vector<wgt_type> edgeWeight(10, 1);

  RandomOrderVertexSet set(0, 10, weight.data(), edgePrefix.data(), \
      edgeList.data(), edgeWeight.data());

  std::vector<bool> marker(weight.size(), false);

  for (Vertex const & vertex : set) {
    marker[vertex.index()] = true;
  }

  for (bool mark : marker) {
    testTrue(mark);
  }
}

}
