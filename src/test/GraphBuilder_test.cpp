/**
* @file GraphBuilder_test.cpp
* @brief Unit tests for the GraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-13
*/



#include "DomTest.hpp"
#include "GraphBuilder.hpp"


namespace dolos
{


UNITTEST(GraphBuilder, FullBuild)
{
  // create a ring of 4 vertices
  GraphBuilder builder;

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
  testEqual(graph.getNumVertices(), 4);
  testEqual(graph.getNumEdges(), 8);

  for (Vertex const & vertex : graph.getVertices()) {
    testEqual(vertex.getWeight(), 1);
    testEqual(vertex.getNumEdges(), 2);

    for (Edge const & edge : vertex.getEdges()) {
      testEqual(edge.getWeight(), 2);
    }
  }
}


}
