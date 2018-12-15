/**
* @file MultilevelPartioner_test.cpp
* @brief Unit tests for the MultilevelPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-04
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


#include "partition/MultilevelPartitioner.hpp"
#include "aggregation/RandomMatchingAggregator.hpp"
#include "partition/BFSBisector.hpp"
#include "partition/RecursiveBisectionPartitioner.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"

#include "solidutils/UnitTest.hpp"

namespace poros
{


UNITTEST(MultilevelPartitioner, ExecuteFullCoarsen8Part)
{
  // build a grid graph
  GridGraphGenerator gen(8, 8, 8);

  RandomEngineHandle engine = RandomEngineFactory::make(0);

  RandomMatchingAggregator rm(engine);

  BFSBisector bfs(engine);
  RecursiveBisectionPartitioner rb(&bfs);

  // TODO: setup the multilevel partition to contract to 8 coarse vertices
}

}
