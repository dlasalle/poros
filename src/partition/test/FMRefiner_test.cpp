/**
* @file FMRefiner_test.cpp
* @brief Unit test for the FMRefiner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-11-05
*/



#include "partition/FMRefiner.hpp"
#include "partition/RandomBisector.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"

namespace dolos
{

UNITTEST(FMRefiner, RefineRandomGridCut)
{
  // graph with 210 vertices and a minimum bisection of 30 
  GridGraphGenerator gen(5, 6, 7); 

  Graph graph = gen.generate();

  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.03);

  FMRefiner fm(25, graph.numVertices());

  RandomEngineHandle engine = RandomEngineFactory::make(0);

  RandomBisector bisector(engine);

  Partitioning part = bisector.execute(&target, &graph); 

  TwoWayConnectivity conn(&graph, &part);

  fm.refine(&target, &conn, &part, &graph);

  testLess(part.getCutEdgeWeight(), 100u);

  PartitioningAnalyzer analyzer(&part, &target);

  testLess(analyzer.calcMaxImbalance(), 0.03005);
}

UNITTEST(FMRefiner, RefineUnbalancedCut)
{
  // graph with 210 vertices and a minimum bisection of 30 
  GridGraphGenerator gen(5, 6, 7); 

  Graph graph = gen.generate();

  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.03);
  Partitioning part(2, &graph);
  part.assignAll(0);
  part.move(Vertex::make(0), 1);
  part.move(Vertex::make(1), 1);
  part.move(Vertex::make(2), 1);
  part.move(Vertex::make(3), 1);
  part.move(Vertex::make(4), 1);
  part.recalcCutEdgeWeight();

  FMRefiner fm(25, graph.numVertices());

  TwoWayConnectivity conn(&graph, &part);

  fm.refine(&target, &conn, &part, &graph);

  testLessOrEqual(part.getCutEdgeWeight(), 60u);

  PartitioningAnalyzer analyzer(&part, &target);

  testLess(analyzer.calcMaxImbalance(), 0.03005);
}

}
