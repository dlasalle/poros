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

  std::vector<vtx_type> neighbors{1,2,3,4,5,6,
      0, 0, 0, 0, 0, 0};
  std::vector<wgt_type> weights(12, 1);
  builder.addVertex(1, 6, neighbors.data(), weights.data());

  builder.addVertex(1, 1, neighbors.data()+6, weights.data()+6);
  builder.addVertex(1, 1, neighbors.data()+7, weights.data()+7);
  builder.addVertex(1, 1, neighbors.data()+8, weights.data()+8);

  builder.addVertex(1, 1, neighbors.data()+9, weights.data()+9);
  builder.addVertex(1, 1, neighbors.data()+10, weights.data()+10);
  builder.addVertex(1, 1, neighbors.data()+11, weights.data()+11);

  ConstantGraph g = builder.finish();

  testEqual(g.numVertices(), 7U);
  testEqual(g.numEdges(), 12U);

  testEqual(g.degreeOf(Vertex::make(0)), 6U);
  testEqual(g.degreeOf(Vertex::make(1)), 1U);
  testEqual(g.degreeOf(Vertex::make(2)), 1U);
  testEqual(g.degreeOf(Vertex::make(3)), 1U);
  testEqual(g.degreeOf(Vertex::make(4)), 1U);
  testEqual(g.degreeOf(Vertex::make(5)), 1U);
}


}

