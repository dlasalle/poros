/**
* @file DiscreteCoarseGraph_test.cpp
* @brief Unit tests for the DiscreteCoarseGraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-10
*/


#include "multilevel/DiscreteCoarseGraph.hpp"
#include "aggregation/Aggregation.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{

UNITTEST(DiscreteCoarseGraph, Contract)
{
  GridGraphGenerator gen(2,8,1);
  ConstantGraph graph = gen.generate();

  std::vector<vtx_type> cmap(graph.numVertices());

  for (size_t i = 0; i < cmap.size(); ++i) {
    cmap[i] = static_cast<vtx_type>(i/2);
  }

  Aggregation agg(std::move(cmap), 8, graph.getData());

  DiscreteCoarseGraph coarse(&graph, &agg);

  ConstantGraph const * coarseGraph = coarse.graph();

  testEqual(coarseGraph->numVertices(), 8U);
  testEqual(coarseGraph->numEdges(), 14U);
}

}
