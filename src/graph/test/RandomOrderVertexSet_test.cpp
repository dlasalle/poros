/**
* @file RandomOrderVertexSet_test.cpp
* @brief Unit tests for the RandomOrderVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2018-01-14
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



#include "graph/RandomOrderVertexSet.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>


namespace poros
{

UNITTEST(RandomOrderVertexSet, Size)
{
  VertexSet vSet(0, 10);

  RandomEngineHandle random = RandomEngineFactory::make(0);

  PermutedVertexSet set = RandomOrderVertexSet::generate(
      vSet, random.get());

  testEqual(set.size(), static_cast<vtx_type>(10));
}


UNITTEST(RandomOrderVertexSet, Iterator)
{
  VertexSet vSet(0, 1732);

  RandomEngineHandle random = RandomEngineFactory::make(0);

  PermutedVertexSet set = RandomOrderVertexSet::generate(
      vSet, random.get());

  std::vector<bool> marker(vSet.size(), false);

  for (Vertex const vertex : set) {
    testFalse(marker[vertex.index]);
    marker[vertex.index] = true;
  }

  for (bool mark : marker) {
    testTrue(mark);
  }
}

}
