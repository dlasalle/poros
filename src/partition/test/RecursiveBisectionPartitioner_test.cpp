/**
* @file RecursiveBisectionPartitioner_test.cpp
* @brief Unit tests for the RecursiveBisectionPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-11
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


#include "partition/RecursiveBisectionPartitioner.hpp"
#include "partition/RandomFMBisector.hpp"
#include "partition/TargetPartitioning.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{

UNITTEST(RecursiveBisectionPartitioner, ExecuteKWayUniform)
{
  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  RandomFMBisector b(8, engine);

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // generate graph
  GridGraphGenerator gen(10, 6, 5);

  for (pid_type k = 2; k < 10; ++k) {
    Graph graph = gen.generate();

    TargetPartitioning target(k, graph.getTotalVertexWeight(), \
        0.03);

    // partition 
    Partitioning part = rb.execute(&target, &graph);
    testEqual(part.numPartitions(), k);

    PartitioningAnalyzer analyzer(&part, &target);

    double const imbalance = analyzer.calcMaxImbalance();
    testLess(imbalance, 0.03005) << "Num partitions = " << k;
  }
}

UNITTEST(RecursiveBisectionPartitioner, ExecuteKWay1To5)
{
  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  RandomFMBisector b(8, engine);

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // generate graph
  GridGraphGenerator gen(9, 5, 7);
  gen.setRandomVertexWeight(1,5);

  for (pid_type k = 2; k < 10; ++k) {
    // create partition parameters
    Graph graph = gen.generate();

    TargetPartitioning target(k, graph.getTotalVertexWeight(), \
        0.03);

    // partition 
    Partitioning part = rb.execute(&target, &graph);
    testEqual(part.numPartitions(), k);

    PartitioningAnalyzer analyzer(&part, &target);

    double const imbalance = analyzer.calcMaxImbalance();
    // TODO: fix balance issues and re-instate this limit
    testLess(imbalance, 0.03005) << "Num partitions = " << k << ", heaviest "
        "partition is " << analyzer.findMostOverWeightPartition() << " (" <<
        analyzer.calcMaxImbalance() << ":" <<
        part.getWeight(analyzer.findMostOverWeightPartition()) << ")" << std::endl;
  }
}

UNITTEST(RecursiveBisectionPartitioner, Execute4Way)
{
  std::vector<double> targets{0.25, 0.3, 0.3, 0.15};

  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  RandomFMBisector b(8, engine);

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // generate graph
  GridGraphGenerator gen(6, 13, 7);
  gen.setRandomVertexWeight(1, 5);

  Graph graph = gen.generate();

  TargetPartitioning target(targets.size(), graph.getTotalVertexWeight(), \
      0.03, targets.data());

  // partition 
  Partitioning part = rb.execute(&target, &graph);
  testEqual(part.numPartitions(), targets.size());
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testLess(imbalance, 0.03005);
}

UNITTEST(RecursiveBisectionPartitioner, Execute7Way1To3)
{
  RandomEngineHandle engine = RandomEngineFactory::make(0);

  // create bisector
  RandomBisector b(engine);

  // create partitioner
  RecursiveBisectionPartitioner rb(&b);

  // create partition parameters
  PartitionParameters params(7);
  params.setImbalanceTolerance(0.01);

  // generate graph
  GridGraphGenerator gen(30, 30, 30);
  gen.setRandomVertexWeight(1, 3);

  Graph graph = gen.generate();
  TargetPartitioning target(7, graph.getTotalVertexWeight(), \
      0.01);

  // partition 
  Partitioning part = rb.execute(&target, &graph);
  testEqual(part.numPartitions(), static_cast<pid_type>(7));
  PartitioningAnalyzer analyzer(&part, &target);

  double const imbalance = analyzer.calcMaxImbalance();
  testLess(imbalance, 0.01005);
}




}
