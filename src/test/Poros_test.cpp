/**
* @file Poros_test.cpp
* @brief Unit tests for the top level API.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-13
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



#include "poros.h"
#include "partition/Partitioning.hpp"
#include "partition/TargetPartitioning.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/Array.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{

UNITTEST(Poros, PartGraphRecursiveSevenBalance)
{
  GridGraphGenerator gen(25, 25, 25);

  Graph g = gen.generate();

  poros_options_struct opts = POROS_defaultOptions();

  // make 10 partitions
  for (size_t i = 0; i < 10U; ++i)  {
    wgt_type cutEdgeWeight;

    opts.randomSeed = static_cast<unsigned int>(i);

    sl::Array<pid_type> where(g.numVertices());
    int r = POROS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
        g.getEdgeList(), g.getVertexWeight(), g.getEdgeWeight(), \
        7, &opts, &cutEdgeWeight, where.data());

    testEqual(r, 1);

    Partitioning part(7, &g, std::move(where)); 
    TargetPartitioning target(part.numPartitions(), \
        g.getTotalVertexWeight(), 0.03);
    PartitioningAnalyzer analyzer(&part, &target);

    double const imbalance = analyzer.calcMaxImbalance();

    testLess(imbalance, 0.03005);
  }
}

UNITTEST(Poros, PartGraphRecursiveTwoCut)
{
  GridGraphGenerator gen(25, 25, 25);

  Graph g = gen.generate();

  // worst of 100 metis runs
  wgt_type const maxAcceptable = 700;

  poros_options_struct opts = POROS_defaultOptions();

  // make 10 partitions
  for (size_t i = 0; i < 10U; ++i)  {
    wgt_type cutEdgeWeight;

    opts.randomSeed = static_cast<unsigned int>(i);

    sl::Array<pid_type> where(g.numVertices());
    int r = POROS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
        g.getEdgeList(), g.getVertexWeight(), g.getEdgeWeight(), \
        2, &opts, &cutEdgeWeight, where.data());

    testEqual(r, 1);

    Partitioning part(2, &g, std::move(where)); 
    TargetPartitioning target(part.numPartitions(), \
        g.getTotalVertexWeight(), 0.03);

    testLessOrEqual(cutEdgeWeight, maxAcceptable);
  }
}

UNITTEST(Poros, PartGraphRecursiveThreeCut)
{
  GridGraphGenerator gen(25, 25, 25);

  Graph g = gen.generate();

  // worst of 100 metis runs
  wgt_type const maxAcceptable = 1375;

  poros_options_struct opts = POROS_defaultOptions();

  // make 10 partitions
  for (size_t i = 0; i < 10U; ++i)  {
    wgt_type cutEdgeWeight;

    opts.randomSeed = static_cast<unsigned int>(i);

    sl::Array<pid_type> where(g.numVertices());
    int r = POROS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
        g.getEdgeList(), g.getVertexWeight(), g.getEdgeWeight(), \
        3, &opts, &cutEdgeWeight, where.data());

    testEqual(r, 1);

    Partitioning part(3, &g, std::move(where)); 
    TargetPartitioning target(part.numPartitions(), \
        g.getTotalVertexWeight(), 0.03);

    testLessOrEqual(cutEdgeWeight, maxAcceptable);
  }
}

UNITTEST(Poros, PartGraphRecursiveFourCut)
{
  GridGraphGenerator gen(25, 25, 25);

  Graph g = gen.generate();

  poros_options_struct opts = POROS_defaultOptions();

  // worst of 100 metis runs
  wgt_type const maxAcceptable = 1650;

  // make 10 partitions
  for (size_t i = 0; i < 1/*0U*/; ++i)  {
    wgt_type cutEdgeWeight;

    opts.randomSeed = static_cast<unsigned int>(i);

    sl::Array<pid_type> where(g.numVertices());
    int r = POROS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
        g.getEdgeList(), g.getVertexWeight(), g.getEdgeWeight(), \
        4, &opts, &cutEdgeWeight, where.data());

    testEqual(r, 1);

    Partitioning part(4, &g, std::move(where)); 
    TargetPartitioning target(part.numPartitions(), \
        g.getTotalVertexWeight(), 0.03);

    testLessOrEqual(cutEdgeWeight, maxAcceptable);
  }
}

UNITTEST(Poros, PartGraphRecursiveSevenCut)
{
  GridGraphGenerator gen(25, 25, 25);

  Graph g = gen.generate();

  // worst of 100 metis runs
  wgt_type const maxAcceptable = 2400;

  poros_options_struct opts = POROS_defaultOptions();

  // make 10 partitions
  for (size_t i = 0; i < 10U; ++i)  {
    wgt_type cutEdgeWeight;

    opts.randomSeed = static_cast<unsigned int>(i);

    sl::Array<pid_type> where(g.numVertices());
    int r = POROS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
        g.getEdgeList(), g.getVertexWeight(), g.getEdgeWeight(), \
        7, &opts, &cutEdgeWeight, where.data());

    testEqual(r, 1);

    Partitioning part(7, &g, std::move(where)); 
    TargetPartitioning target(part.numPartitions(), \
        g.getTotalVertexWeight(), 0.03);

    testLessOrEqual(cutEdgeWeight, maxAcceptable);
  }
}

UNITTEST(Poros, PartGraphNullEdgeWeight)
{
  GridGraphGenerator gen(5, 5, 5);

  Graph g = gen.generate();

  poros_options_struct opts = POROS_defaultOptions();

  // make 10 partitions
  wgt_type cutEdgeWeight;

  opts.randomSeed = static_cast<unsigned int>(0);

  sl::Array<pid_type> where(g.numVertices());
  int r = POROS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
      g.getEdgeList(), g.getVertexWeight(), nullptr, \
      3, &opts, &cutEdgeWeight, where.data());

  testEqual(r, 1);
}

UNITTEST(Poros, PartGraphNullVertexWeight)
{
  GridGraphGenerator gen(5, 5, 5);

  Graph g = gen.generate();

  poros_options_struct opts = POROS_defaultOptions();

  // make 10 partitions
  wgt_type cutEdgeWeight;

  opts.randomSeed = static_cast<unsigned int>(0);

  sl::Array<pid_type> where(g.numVertices());
  int r = POROS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
      g.getEdgeList(), nullptr, g.getEdgeWeight(), \
      3, &opts, &cutEdgeWeight, where.data());

  testEqual(r, 1);
}

UNITTEST(Poros, PartGraphNullWeights)
{
  GridGraphGenerator gen(5, 5, 5);

  Graph g = gen.generate();

  poros_options_struct opts = POROS_defaultOptions();

  // make 10 partitions
  wgt_type cutEdgeWeight;

  opts.randomSeed = static_cast<unsigned int>(0);

  sl::Array<pid_type> where(g.numVertices());
  int r = POROS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
      g.getEdgeList(), nullptr, nullptr, \
      3, &opts, &cutEdgeWeight, where.data());

  testEqual(r, 1);
}

}
