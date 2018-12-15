/**
* @file BFSBisector_test.cpp
* @brief Unit tests for the BFSBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-08
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
#include "partition/BFSBisector.hpp"
#include "partition/TargetPartitioning.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{

UNITTEST(BFSBisector, ExecuteUniform)
{
  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  BFSBisector b(engine);

  // generate graph
  GridGraphGenerator gen(40, 40, 1);

  Graph graph = gen.generate();

  // setup parameters
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.0);

  // perform bisection
  Partitioning part = b.execute(&target, &graph);

  std::vector<double> targets{0.5, 0.5};
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testEqual(imbalance, 0.0);
}


UNITTEST(BFSBisector, Execute1To5)
{
  std::vector<double> targets{0.4, 0.6};

  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  BFSBisector b(engine);

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


UNITTEST(BFSBisector, ExecuteCut)
{
  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  BFSBisector b(engine);

  // generate graph
  GridGraphGenerator gen(40, 40, 1);

  Graph graph = gen.generate();

  // setup parameters
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.0);

  // perform bisection
  Partitioning part = b.execute(&target, &graph);

  wgt_type const maxCut = 80;
  wgt_type const minCut = 40;

  testLessOrEqual(part.getCutEdgeWeight(), maxCut);
  testGreaterOrEqual(part.getCutEdgeWeight(), minCut);

  PartitioningAnalyzer analyzer(&part, &target);

  // balanced to within 0.1%
  testLess(analyzer.calcMaxImbalance(), 0.001);
}


}
