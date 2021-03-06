/**
* @file RandomBisector_test.cpp
* @brief Unit tests for the RandomBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-09
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


#include "partition/Partitioning.hpp"
#include "partition/RandomBisector.hpp"
#include "partition/TargetPartitioning.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{

UNITTEST(RandomBisector, ExecuteUniform)
{
  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  RandomBisector b(engine);

  // generate graph
  GridGraphGenerator gen(40, 40, 1);

  Graph graph = gen.generate();

  // setup parameters
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.0);

  // perform bisection
  Partitioning part = b.execute(&target, &graph);

  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testEqual(imbalance, 0.0);
}


UNITTEST(RandomBisector, Execute1To5)
{
  std::vector<double> targets{0.4, 0.6};

  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  RandomBisector b(engine);

  // generate graph
  GridGraphGenerator gen(40, 40, 1);
  gen.setRandomVertexWeight(1, 5);

  Graph graph = gen.generate();

  // setup parameters
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.0, \
      targets.data());

  // perform bisection
  Partitioning part = b.execute(&target, &graph);
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testLess(imbalance, 0.001);
}


UNITTEST(RandomBisector, ExecuteCut)
{
  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  RandomBisector b(engine);

  // generate graph
  GridGraphGenerator gen(40, 40, 1);

  Graph graph = gen.generate();

  // setup parameters
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.0);

  // perform bisection
  Partitioning part = b.execute(&target, &graph);

  wgt_type maxCut = graph.getTotalEdgeWeight() / 2;
  wgt_type minCut = 40;

  testLessOrEqual(part.getCutEdgeWeight(), maxCut);
  testGreaterOrEqual(part.getCutEdgeWeight(), minCut);
}


}
