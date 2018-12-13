/**
* @file Dolos_test.cpp
* @brief Unit tests for the top level API.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-13
*/



#include "dolos.h"
#include "partition/Partitioning.hpp"
#include "partition/TargetPartitioning.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/Array.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{

UNITTEST(Dolos, PartGraphRecursiveSevenBalance)
{
  GridGraphGenerator gen(25, 25, 25);

  Graph g = gen.generate();

  dolos_options_struct opts = DOLOS_defaultOptions();

  // make 10 partitions
  for (size_t i = 0; i < 10U; ++i)  {
    wgt_type cutEdgeWeight;

    opts.randomSeed = static_cast<unsigned int>(i);

    sl::Array<pid_type> where(g.numVertices());
    int r = DOLOS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
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

UNITTEST(Dolos, PartGraphRecursiveTwoCut)
{
  GridGraphGenerator gen(25, 25, 25);

  Graph g = gen.generate();

  // worst of 100 metis runs
  wgt_type const maxAcceptable = 700;

  dolos_options_struct opts = DOLOS_defaultOptions();

  // make 10 partitions
  for (size_t i = 0; i < 10U; ++i)  {
    wgt_type cutEdgeWeight;

    opts.randomSeed = static_cast<unsigned int>(i);

    sl::Array<pid_type> where(g.numVertices());
    int r = DOLOS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
        g.getEdgeList(), g.getVertexWeight(), g.getEdgeWeight(), \
        2, &opts, &cutEdgeWeight, where.data());

    testEqual(r, 1);

    Partitioning part(2, &g, std::move(where)); 
    TargetPartitioning target(part.numPartitions(), \
        g.getTotalVertexWeight(), 0.03);

    testLessOrEqual(cutEdgeWeight, maxAcceptable);
  }
}

UNITTEST(Dolos, PartGraphRecursiveThreeCut)
{
  GridGraphGenerator gen(25, 25, 25);

  Graph g = gen.generate();

  // worst of 100 metis runs
  wgt_type const maxAcceptable = 1375;

  dolos_options_struct opts = DOLOS_defaultOptions();

  // make 10 partitions
  for (size_t i = 0; i < 10U; ++i)  {
    wgt_type cutEdgeWeight;

    opts.randomSeed = static_cast<unsigned int>(i);

    sl::Array<pid_type> where(g.numVertices());
    int r = DOLOS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
        g.getEdgeList(), g.getVertexWeight(), g.getEdgeWeight(), \
        3, &opts, &cutEdgeWeight, where.data());

    testEqual(r, 1);

    Partitioning part(3, &g, std::move(where)); 
    TargetPartitioning target(part.numPartitions(), \
        g.getTotalVertexWeight(), 0.03);

    testLessOrEqual(cutEdgeWeight, maxAcceptable);
  }
}

UNITTEST(Dolos, PartGraphRecursiveFourCut)
{
  GridGraphGenerator gen(25, 25, 25);

  Graph g = gen.generate();

  dolos_options_struct opts = DOLOS_defaultOptions();

  // worst of 100 metis runs
  wgt_type const maxAcceptable = 1650;

  // make 10 partitions
  for (size_t i = 0; i < 1/*0U*/; ++i)  {
    wgt_type cutEdgeWeight;

    opts.randomSeed = static_cast<unsigned int>(i);

    sl::Array<pid_type> where(g.numVertices());
    int r = DOLOS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
        g.getEdgeList(), g.getVertexWeight(), g.getEdgeWeight(), \
        4, &opts, &cutEdgeWeight, where.data());

    testEqual(r, 1);

    Partitioning part(4, &g, std::move(where)); 
    TargetPartitioning target(part.numPartitions(), \
        g.getTotalVertexWeight(), 0.03);

    testLessOrEqual(cutEdgeWeight, maxAcceptable);
  }
}

UNITTEST(Dolos, PartGraphRecursiveSevenCut)
{
  GridGraphGenerator gen(25, 25, 25);

  Graph g = gen.generate();

  // worst of 100 metis runs
  wgt_type const maxAcceptable = 2400;

  dolos_options_struct opts = DOLOS_defaultOptions();

  // make 10 partitions
  for (size_t i = 0; i < 10U; ++i)  {
    wgt_type cutEdgeWeight;

    opts.randomSeed = static_cast<unsigned int>(i);

    sl::Array<pid_type> where(g.numVertices());
    int r = DOLOS_PartGraphRecursive(g.numVertices(), g.getEdgePrefix(), \
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
