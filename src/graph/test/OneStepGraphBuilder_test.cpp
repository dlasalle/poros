/**
* @file OneStepGraphBuilder_test.cpp
* @brief Unit tests for the OneStepGraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-24
*/

#include "graph/OneStepGraphBuilder.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>

namespace dolos
{

/******************************************************************************
* UNIT TESTS ******************************************************************
******************************************************************************/

UNITTEST(OneStepGraphBuilderTest, BuildStar)
{
  OneStepGraphBuilder builder(7, 12);

  builder.addEdge(1, 1);
  builder.addEdge(2, 1);
  builder.addEdge(3, 1);
  builder.addEdge(4, 1);
  builder.addEdge(5, 1);
  builder.addEdge(6, 1);
  builder.finishVertex(1);

  builder.addEdge(0, 1);
  builder.finishVertex(1);

  builder.addEdge(0, 1);
  builder.finishVertex(1);

  builder.addEdge(0, 1);
  builder.finishVertex(1);

  builder.addEdge(0, 1);
  builder.finishVertex(1);

  builder.addEdge(0, 1);
  builder.finishVertex(1);

  builder.addEdge(0, 1);
  builder.finishVertex(1);

  GraphHandle g = builder.finish();

  testEqual(g->numVertices(), 7U);
  testEqual(g->numEdges(), 12U);

  testEqual(g->degreeOf(Vertex::make(0)), 6U);
  testEqual(g->degreeOf(Vertex::make(1)), 1U);
  testEqual(g->degreeOf(Vertex::make(2)), 1U);
  testEqual(g->degreeOf(Vertex::make(3)), 1U);
  testEqual(g->degreeOf(Vertex::make(4)), 1U);
  testEqual(g->degreeOf(Vertex::make(5)), 1U);
}


}

