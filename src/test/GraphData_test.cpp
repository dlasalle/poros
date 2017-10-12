/**
* @file GraphData_test.cpp
* @brief Unit tests for the GraphData class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-12
*/


#include <vector>
#include "GraphData.hpp"
#include "ConstantGraph.hpp"
#include "DomTest.hpp"


namespace dolos
{


UNITTEST(ConstantGraph, ConstructionAndGet)
{
  GraphData gd(5, 8);

  testEqual(gd.getNumVertices(), 5);
  testEqual(gd.getNumEdges(), 8);

  // write to every vertex weight location 
  for (vtx_type v = 0; v < 5; ++v) {
    gd.getVertexWeight()[v] = 1; 
  }

  // write to every edgePrefix location 
  for (vtx_type v = 0; v < 6; ++v) {
    gd.getEdgePrefix()[v] = static_cast<adj_type>(2*v);
  }

  // write to every edge location
  for (adj_type e = 0; e < 8; ++e) {
    gd.getEdgeList()[e] = static_cast<vtx_type>(e);
    gd.getEdgeWeight()[e] = 2;
  }

  // verify that what we wrote is still there and use constant getters
  {
    GraphData const * const cgd = &gd;

    for (vtx_type v = 0; v < 5; ++v) {
      testEqual(cgd->getVertexWeight()[v], 1); 
    }

    // write to every edgePrefix location 
    for (vtx_type v = 0; v < 6; ++v) {
      testEqual(cgd->getEdgePrefix()[v], static_cast<adj_type>(2*v));
    }

    // write to every edge location
    for (adj_type e = 0; e < 8; ++e) {
      testEqual(cgd->getEdgeList()[e], static_cast<vtx_type>(e));
      testEqual(cgd->getEdgeWeight()[e], 2);
    }
  }
}


UNITTEST(ConstantGraph, MoveGet)
{
  GraphData gd(5, 8);

  testEqual(gd.getNumVertices(), 5);
  testEqual(gd.getNumEdges(), 8);

  // write to every vertex weight location 
  for (vtx_type v = 0; v < 5; ++v) {
    gd.getVertexWeight()[v] = 1; 
  }

  // write to every edgePrefix location 
  for (vtx_type v = 0; v < 6; ++v) {
    gd.getEdgePrefix()[v] = static_cast<adj_type>(2*v);
  }

  // write to every edge location
  for (adj_type e = 0; e < 8; ++e) {
    gd.getEdgeList()[e] = static_cast<vtx_type>(e);
    gd.getEdgeWeight()[e] = 2;
  }

  // verify that what we wrote is still there and use constant getters
  {
    GraphData const cgd = std::move(gd);

    for (vtx_type v = 0; v < 5; ++v) {
      testEqual(cgd.getVertexWeight()[v], 1); 
    }

    // write to every edgePrefix location 
    for (vtx_type v = 0; v < 6; ++v) {
      testEqual(cgd.getEdgePrefix()[v], static_cast<adj_type>(2*v));
    }

    // write to every edge location
    for (adj_type e = 0; e < 8; ++e) {
      testEqual(cgd.getEdgeList()[e], static_cast<vtx_type>(e));
      testEqual(cgd.getEdgeWeight()[e], 2);
    }
  }

}

UNITTEST(ConstantGraph, ToGraph)
{
  std::vector<adj_type> prefix{0, 1, 3, 5, 6};
  std::vector<wgt_type> vwgt{1, 2, 4, 3};
  std::vector<vtx_type> adjncy{1, 0, 2, 1, 3, 2};
  std::vector<wgt_type> ewgt{8, 8, 9, 9, 7, 7};

  GraphData gd(vwgt.size(), adjncy.size());

  // write to every vertex weight location 
  for (vtx_type v = 0; v < vwgt.size(); ++v) {
    gd.getVertexWeight()[v] = vwgt[v]; 
  }

  // write to every edgePrefix location 
  for (vtx_type v = 0; v < prefix.size(); ++v) {
    gd.getEdgePrefix()[v] = prefix[v];
  }

  // write to every edge location
  for (adj_type e = 0; e < adjncy.size(); ++e) {
    gd.getEdgeList()[e] = adjncy[e];
    gd.getEdgeWeight()[e] = ewgt[e];
  }

  // convert to graph and verify graph 
  ConstantGraph const g = gd.toGraph();

  testEqual(g.getNumVertices(), vwgt.size());
  testEqual(g.getNumEdges(), ewgt.size());

  for (Vertex const & v : g.getVertices()) {
    testEqual(v.getWeight(), vwgt[v.getIndex()]);

    testEqual(prefix[v.getIndex()+1] - prefix[v.getIndex()], v.getNumEdges());

    for (Edge const & e : v.getEdges()) {
      testEqual(e.getVertex(), adjncy[e.getIndex()]);
      testEqual(e.getWeight(), ewgt[e.getIndex()]); 
    }
  }
}

}
