/**
* @file SummationContractor_test.cpp
* @brief Unit tests for the SummationContractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
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

UNITTEST(SummationContractor, ContractLine)
{
  GridGraphGenerator gen(2,8,1);
  ConstantGraph graph = gen.generate();

  std::vector<vtx_type> cmap(graph.numVertices());

  for (size_t i = 0; i < cmap.size(); ++i) {
    cmap[i] = static_cast<vtx_type>(i/2);
  }

  Aggregation agg(std::move(cmap), 8, graph.getData());

  SummationContractor contractor;

  // the coarse graph should just be a line with 8 vertices and every edge
  // should be of weight 2
  ConstantGraph out = contractor.contract(&graph, &agg);

  testEqual(out.numVertices(), agg.getNumCoarseVertices());

  testEqual(out.degreeOf(Vertex::make(0)), static_cast<vtx_type>(1));
  testEqual(out.degreeOf(Vertex::make(1)), static_cast<vtx_type>(2));
  testEqual(out.degreeOf(Vertex::make(2)), static_cast<vtx_type>(2));
  testEqual(out.degreeOf(Vertex::make(3)), static_cast<vtx_type>(2));
  testEqual(out.degreeOf(Vertex::make(4)), static_cast<vtx_type>(2));
  testEqual(out.degreeOf(Vertex::make(5)), static_cast<vtx_type>(2));
  testEqual(out.degreeOf(Vertex::make(6)), static_cast<vtx_type>(2));
  testEqual(out.degreeOf(Vertex::make(7)), static_cast<vtx_type>(1));

  for (Edge const & edge : out.edges()) {
    testEqual(out.weightOf(edge), static_cast<wgt_type>(2));
  }
}

UNITTEST(SummationContractor, ContractCubeComplete)
{
  GridGraphGenerator gen(2,2,2);
  gen.setRandomEdgeWeight(10,10);
  ConstantGraph graph = gen.generate();

  std::vector<vtx_type> cmap(graph.numVertices());

  cmap[0] = static_cast<vtx_type>(0);
  cmap[1] = static_cast<vtx_type>(0);

  cmap[2] = static_cast<vtx_type>(1);
  cmap[3] = static_cast<vtx_type>(1);

  cmap[4] = static_cast<vtx_type>(2);
  cmap[6] = static_cast<vtx_type>(2);

  cmap[5] = static_cast<vtx_type>(3);
  cmap[7] = static_cast<vtx_type>(3);

  Aggregation agg(std::move(cmap), 8, graph.getData());

  SummationContractor contractor;

  // the coarse graph should just be a line with 8 vertices and every edge
  // should be of weight 2
  ConstantGraph out = contractor.contract(&graph, &agg);

  testEqual(out.numVertices(), agg.getNumCoarseVertices());

  testEqual(out.degreeOf(Vertex::make(0)), static_cast<vtx_type>(3));
  testEqual(out.degreeOf(Vertex::make(1)), static_cast<vtx_type>(3));
  testEqual(out.degreeOf(Vertex::make(2)), static_cast<vtx_type>(3));
  testEqual(out.degreeOf(Vertex::make(3)), static_cast<vtx_type>(3));

  testEqual(out.getTotalEdgeWeight(), static_cast<wgt_type>(160));
}

UNITTEST(SummationContractor, ContractCubeSquare)
{
  GridGraphGenerator gen(2,2,2);
  ConstantGraph graph = gen.generate();

  std::vector<vtx_type> cmap(graph.numVertices());

  cmap[0] = static_cast<vtx_type>(0);
  cmap[1] = static_cast<vtx_type>(0);

  cmap[2] = static_cast<vtx_type>(1);
  cmap[3] = static_cast<vtx_type>(1);

  cmap[4] = static_cast<vtx_type>(2);
  cmap[5] = static_cast<vtx_type>(2);

  cmap[6] = static_cast<vtx_type>(3);
  cmap[7] = static_cast<vtx_type>(3);

  Aggregation agg(std::move(cmap), 8, graph.getData());

  SummationContractor contractor;

  // the coarse graph should just be a line with 8 vertices and every edge
  // should be of weight 2
  ConstantGraph out = contractor.contract(&graph, &agg);

  testEqual(out.numVertices(), agg.getNumCoarseVertices());

  testEqual(out.degreeOf(Vertex::make(0)), static_cast<vtx_type>(2));
  testEqual(out.degreeOf(Vertex::make(1)), static_cast<vtx_type>(2));
  testEqual(out.degreeOf(Vertex::make(2)), static_cast<vtx_type>(2));
  testEqual(out.degreeOf(Vertex::make(3)), static_cast<vtx_type>(2));

  testEqual(out.getTotalEdgeWeight(), static_cast<wgt_type>(16));

  for (Edge const & edge : out.edges()) {
    testEqual(out.weightOf(edge), static_cast<wgt_type>(2));
  }
}




}
