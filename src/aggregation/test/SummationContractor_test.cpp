/**
* @file SummationContractor_test.cpp
* @brief Unit tests for the SummationContractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-01-18
*/



#include "aggregation/SummationContractor.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{


/******************************************************************************
* UNIT TESTS ******************************************************************
******************************************************************************/

UNITTEST(SummationContractor, Contract)
{
  GridGraphGenerator gen(2,8,1);
  ConstantGraph graph = gen.generate();

  std::vector<vtx_type> cmap(graph.getNumVertices());

  for (size_t i = 0; i < cmap.size(); ++i) {
    cmap[i] = static_cast<vtx_type>(i/2);
  }

  Aggregation agg(std::move(cmap), 8, graph.getData());

  SummationContractor contractor;

  // the coarse graph should just be a line with 8 vertices and every edge
  // should be of weight 2
  ConstantGraph out = contractor.contract(&graph, &agg);

  testEqual(out.getNumVertices(), agg.getNumCoarseVertices());

  testEqual(out.getVertex(0).degree(), static_cast<vtx_type>(1));
  testEqual(out.getVertex(1).degree(), static_cast<vtx_type>(2));
  testEqual(out.getVertex(2).degree(), static_cast<vtx_type>(2));
  testEqual(out.getVertex(3).degree(), static_cast<vtx_type>(2));
  testEqual(out.getVertex(4).degree(), static_cast<vtx_type>(2));
  testEqual(out.getVertex(5).degree(), static_cast<vtx_type>(2));
  testEqual(out.getVertex(6).degree(), static_cast<vtx_type>(2));
  testEqual(out.getVertex(7).degree(), static_cast<vtx_type>(1));

  for (Edge const & edge : out.edges()) {
    testEqual(edge.weight(), static_cast<wgt_type>(2));
  }
}


}
