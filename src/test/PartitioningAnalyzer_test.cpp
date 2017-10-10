/**
* @file PartitioningAnalyzer_test.cpp
* @brief Unit tests for the PartitioningAnalyzer class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/


#include "DomTest.hpp"
#include "GridGraphGenerator.hpp"
#include "Partitioning.hpp"
#include "PartitioningAnalyzer.hpp"


namespace dolos
{


UNITTEST(PartitioningAnalyzer, CalcMaxImbalance)
{
  std::vector<double> targets{0.5, 0.5};

  // generate graph
  GridGraphGenerator gen(2, 2, 1);

  ConstantGraph graph = gen.generate();

  Partitioning part(2, graph.getNumVertices());
  part.assignAll(0, graph.getTotalVertexWeight());

  part.move(0, 1, graph.getVertexWeight()[0]);

  // verify its balanced
  PartitioningAnalyzer analyzer(&graph, &part);

  double imbalance = analyzer.calcMaxImbalance(targets.data());
  testEqual(imbalance, 0.5);
}


}
