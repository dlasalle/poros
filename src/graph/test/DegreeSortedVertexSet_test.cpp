/**
* @file DegreeSortedVertexSet_test.cpp
* @brief Unit tests for the DegreeSortedVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-23
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/


#include "graph/DegreeSortedVertexSet.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>


namespace poros
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

  testEqual(set.size(), static_cast<vtx_type>(10));

  vtx_type lastDegree = 0;
  for (Vertex const vertex : set) {
    testLess(lastDegree, edgePrefix[vertex.index+1] -edgePrefix[vertex.index]);
  }
}


}
