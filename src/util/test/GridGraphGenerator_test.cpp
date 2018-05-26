/**
* @file GridGraphGenerator_test.cpp
* @brief Unit tests for the GridGraphGenerator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/


#include "util/GridGraphGenerator.hpp"
#include "graph/ConstantGraph.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{


UNITTEST(RandomBisector, Execute)
{
  // generate graph
  GridGraphGenerator gen(17, 10, 3);
  gen.setRandomVertexWeight(1, 3);

  ConstantGraph graph = gen.generate();

  testEqual(graph.getNumVertices(), static_cast<vtx_type>(17*10*3));

  wgt_type const * const vertexWeight = graph.getVertexWeight();
  for (vtx_type v = 0; v < graph.getNumVertices(); ++v) {
    testGreaterOrEqual(vertexWeight[v], static_cast<wgt_type>(1));
    testLessOrEqual(vertexWeight[v], static_cast<wgt_type>(3));
  }
}


}
