/**
* @file Poros_test.cpp
* @brief Unit tests for the top level API.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-13
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

}
