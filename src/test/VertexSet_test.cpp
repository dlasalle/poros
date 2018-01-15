/**
* @file VertexSet_test.cpp
* @brief Unit tests for the VertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2018-01-14
*/



#include "VertexSet.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>



namespace dolos
{

UNITTEST(VertexSet, Size)
{
  std::vector<wgt_type> weight(10, 1);
  std::vector<adj_type> edgePrefix{0,1,2,3,4,5,6,7,8,9,10};;
  std::vector<vtx_type> edgeList{0,1,2,3,4,5,6,7,8,9};
  std::vector<wgt_type> edgeWeight(10, 1);

  VertexSet set(0, 10, weight.data(), edgePrefix.data(), edgeList.data(), \
      edgeWeight.data());

  testEqual(set.size(), 10U);
}


UNITTEST(VertexSet, Iterator)
{
  std::vector<wgt_type> weight(10, 1);
  std::vector<adj_type> edgePrefix{0,1,2,3,4,5,6,7,8,9,10};;
  std::vector<vtx_type> edgeList{0,1,2,3,4,5,6,7,8,9};
  std::vector<wgt_type> edgeWeight(10, 1);

  VertexSet set(0, 10, weight.data(), edgePrefix.data(), edgeList.data(), \
      edgeWeight.data());

  vtx_type v = 0;
  for (Vertex const & vertex : set) {
    testEqual(vertex.index(), v);
    ++v; 
  }
}

}
