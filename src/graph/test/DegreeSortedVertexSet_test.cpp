/**
* @file DegreeSortedVertexSet_test.cpp
* @brief Unit tests for the DegreeSortedVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-23
*/


#include "graph/DegreeSortedVertexSet.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>


namespace dolos
{

UNITTEST(DegreeSortedVertexSet, Size)
{
  std::vector<wgt_type> weight(10, 1);
  std::vector<adj_type> edgePrefix{0,1,2,4,5,6,7,8,9,10,12};;
  std::vector<vtx_type> edgeList{0,1,2,3,4,5,6,7,8,9,10,11};
  std::vector<wgt_type> edgeWeight(12, 1);

  Graph g(edgePrefix.size()-1, edgePrefix.back(), edgePrefix.data(),
      edgeList.data(), weight.data(), edgeWeight.data());

  VertexSet vSet(0, edgePrefix.size()-1);

  PermutedVertexSet set = DegreeSortedVertexSet::ascending(vSet, &g);

  testEqual(set.size(), 10U);

  vtx_type lastDegree = 0;
  for (Vertex const vertex : set) {
    testLess(lastDegree, edgePrefix[vertex.index+1] -edgePrefix[vertex.index]);
  }
}


}
