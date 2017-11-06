/**
* @file FMRefiner_test.cpp
* @brief Unit test for the FMRefiner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-11-05
*/


#include "solidutils/UnitTest.hpp"

#include "FMRefiner.hpp"
#include "GridGraphGenerator.hpp"
#include "RandomBisector.hpp"

namespace dolos
{

UNITTEST(FMRefiner, RefineRandomGridCut)
{
  // graph with 1320 vertices and a minimum bisection of 110
  GridGraphGenerator gen(10, 11, 12); 

  ConstantGraph graph = gen.generate();

  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.03);

  FMRefiner fm(25);

  RandomBisector bisector;

  Partitioning part = bisector.execute(&target, &graph); 

  TwoWayConnectivity conn(&graph, &part);

  fm.refine(&target, &conn, &part, &graph);

  testEqual(part.getCutEdgeWeight(), 110);
}


}
