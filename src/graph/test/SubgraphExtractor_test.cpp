/**
* @file SubgraphExtractor_test.cpp
* @brief Unit tests for the SubgraphExtractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-12
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



#include "graph/SubgraphExtractor.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{

UNITTEST(SubgraphExtract, Partitions)
{
  GridGraphGenerator gen(2,2,2);

  Graph g = gen.generate(); 

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
