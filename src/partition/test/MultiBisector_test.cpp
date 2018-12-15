/**
* @file MultiBisector_test.cpp
* @brief Unit tests for the MultiBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-20
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


#include "partition/MultiBisector.hpp"
#include "partition/RandomBisector.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{

UNITTEST(MultiBisector, ExecuteUniform)
{
  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  std::unique_ptr<IBisector> b(new RandomBisector(engine));
  MultiBisector mb(10, std::move(b));

  // generate graph
  GridGraphGenerator gen(40, 40, 1);

  Graph graph = gen.generate();

  // setup parameters
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.0);

  // perform bisection
  Partitioning part = mb.execute(&target, &graph);

  // ensure its balanced
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testEqual(imbalance, 0.0);

  // make 10 random bisections and expect the result to be better than average
  wgt_type cutEdges = 0;
  b.reset(new RandomBisector(engine));
  for (int i = 0; i < 10; ++i) {
    Partitioning testPart = b->execute(&target, &graph);
    
    cutEdges += testPart.getCutEdgeWeight();
  }
  cutEdges /= 10;

  testLess(part.getCutEdgeWeight(), cutEdges);
}
  
}
