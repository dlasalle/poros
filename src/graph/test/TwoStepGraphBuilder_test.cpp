/**
* @file TwoStepGraphBuilder_test.cpp
* @brief Unit tests for the TwoStepGraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-13
*/



#include "graph/TwoStepGraphBuilder.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{


UNITTEST(TwoStepGraphBuilder, FullBuild)
{
  // create a ring of 4 vertices
  TwoStepGraphBuilder builder;

  builder.setNumVertices(4);
  builder.beginVertexPhase();

  builder.incVertexNumEdges(0);
  builder.incVertexNumEdges(1);
  builder.incVertexNumEdges(2);
  builder.incVertexNumEdges(3);

  builder.incVertexNumEdges(2);
  builder.incVertexNumEdges(3);
  builder.incVertexNumEdges(1);
  builder.incVertexNumEdges(0);

  builder.setVertexWeight(0, 1);
  builder.setVertexWeight(1, 1);
  builder.setVertexWeight(2, 1);
  builder.setVertexWeight(3, 1);

  builder.beginEdgePhase();

  builder.addEdgeToVertex(0, 1, 2);
  builder.addEdgeToVertex(1, 2, 2);
  builder.addEdgeToVertex(2, 3, 2);
  builder.addEdgeToVertex(3, 0, 2);

  builder.addEdgeToVertex(3, 2, 2);
  builder.addEdgeToVertex(1, 0, 2);
  builder.addEdgeToVertex(0, 3, 2);
  builder.addEdgeToVertex(2, 1, 2);

  ConstantGraph graph = builder.finish();

  // verify graph
  testEqual(graph.numVertices(), 4u);
  testEqual(graph.numEdges(), 8u);

  for (Vertex const & vertex : graph.vertices()) {
    testEqual(vertex.weight(), 1u);
    testEqual(vertex.degree(), 2u);

    for (Edge const & edge : vertex.edges()) {
      testEqual(edge.weight(), 2u);
    }
  }
}


}
