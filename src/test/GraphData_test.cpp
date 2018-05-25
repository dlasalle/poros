/**
* @file GraphData_test.cpp
* @brief Unit tests for the GraphData class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-12
*/


#include "GraphData.hpp"
#include "ConstantGraph.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>


namespace dolos
{


UNITTEST(GraphData, ConstructionAndGet)
{
  GraphData gd(5, 10);

  // write to every vertex weight location 
  for (vtx_type v = 0; v < 5; ++v) {
    gd.vertexWeight()[v] = 1; 
  }

  // write to every edgePrefix location 
  for (vtx_type v = 0; v < 6; ++v) {
    gd.edgePrefix()[v] = static_cast<adj_type>(2*v);
  }

  // write to every edge location
  for (adj_type e = 0; e < 10; ++e) {
    gd.edgeList()[e] = static_cast<vtx_type>(e);
    gd.edgeWeight()[e] = 2;
  }

  testEqual(gd.getNumVertices(), 5u);
  testEqual(gd.getNumEdges(), 10u);

  // verify that what we wrote is still there and use constant getters
  {
    GraphData const * const cgd = &gd;

    for (vtx_type v = 0; v < 5; ++v) {
      testEqual(cgd->vertexWeight()[v], 1u); 
    }

    // write to every edgePrefix location 
    for (vtx_type v = 0; v < 6; ++v) {
      testEqual(cgd->edgePrefix()[v], static_cast<adj_type>(2*v));
    }

    // write to every edge location
    for (adj_type e = 0; e < 10; ++e) {
      testEqual(cgd->edgeList()[e], static_cast<vtx_type>(e));
      testEqual(cgd->edgeWeight()[e], 2u);
    }
  }
}


UNITTEST(GraphData, MoveGet)
{
  GraphData gd(5, 10);

  // write to every vertex weight location 
  for (vtx_type v = 0; v < 5; ++v) {
    gd.vertexWeight()[v] = 1; 
  }

  // write to every edgePrefix location 
  for (vtx_type v = 0; v < 6; ++v) {
    gd.edgePrefix()[v] = static_cast<adj_type>(2*v);
  }

  // write to every edge location
  for (adj_type e = 0; e < 10; ++e) {
    gd.edgeList()[e] = static_cast<vtx_type>(e);
    gd.edgeWeight()[e] = 2;
  }

  // test graph size now that we've filled it out
  testEqual(gd.getNumVertices(), 5u);
  testEqual(gd.getNumEdges(), 10u);

  // verify that what we wrote is still there and use constant getters
  {
    GraphData const cgd = std::move(gd);

    for (vtx_type v = 0; v < 5; ++v) {
      testEqual(cgd.vertexWeight()[v], 1u); 
    }

    // write to every edgePrefix location 
    for (vtx_type v = 0; v < 6; ++v) {
      testEqual(cgd.edgePrefix()[v], static_cast<adj_type>(2*v));
    }

    // write to every edge location
    for (adj_type e = 0; e < 10; ++e) {
      testEqual(cgd.edgeList()[e], static_cast<vtx_type>(e));
      testEqual(cgd.edgeWeight()[e], 2u);
    }
  }

}

UNITTEST(GraphData, ToGraph)
{
  std::vector<adj_type> prefix{0, 1, 3, 5, 6};
  std::vector<wgt_type> vwgt{1, 2, 4, 3};
  std::vector<vtx_type> adjncy{1, 0, 2, 1, 3, 2};
  std::vector<wgt_type> ewgt{8, 8, 9, 9, 7, 7};

  GraphData gd(vwgt.size(), adjncy.size());

  // write to every vertex weight location 
  for (vtx_type v = 0; v < vwgt.size(); ++v) {
    gd.vertexWeight()[v] = vwgt[v]; 
  }

  // write to every edgePrefix location 
  for (vtx_type v = 0; v < prefix.size(); ++v) {
    gd.edgePrefix()[v] = prefix[v];
  }

  // write to every edge location
  for (adj_type e = 0; e < adjncy.size(); ++e) {
    gd.edgeList()[e] = adjncy[e];
    gd.edgeWeight()[e] = ewgt[e];
  }

  // convert to graph and verify graph 
  ConstantGraph const g = gd.toGraph();

  testEqual(g.getNumVertices(), vwgt.size());
  testEqual(g.getNumEdges(), ewgt.size());

  for (Vertex const & v : g.getVertices()) {
    testEqual(v.weight(), vwgt[v.index()]);

    testEqual(prefix[v.index()+1] - prefix[v.index()], v.degree());

    for (Edge const & e : v.getEdges()) {
      testEqual(e.destination(), adjncy[e.index()]);
      testEqual(e.weight(), ewgt[e.index()]); 
    }
  }
}

}
