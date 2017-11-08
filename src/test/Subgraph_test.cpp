/**
* @file Subgraph_test.cpp
* @brief Unit tests for the Subgraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-12
*/

#include "solidutils/UnitTest.hpp"
#include "Subgraph.hpp"
#include "ConstantGraph.hpp"
#include "GridGraphGenerator.hpp"
#include "solidutils/Array.hpp"
#include "solidutils/VectorMath.hpp"


namespace dolos
{


UNITTEST(Subgraph, GetGraph)
{
  GridGraphGenerator gen(5, 5, 5);

  ConstantGraph g = gen.generate();

  sl::Array<vtx_type> superMap(g.getNumVertices());
  sl::VectorMath::increment(superMap.data(), superMap.size(), 1U);

  Subgraph s(&g, &superMap);

  testEqual(s.getGraph()->getNumVertices(), static_cast<vtx_type>(5*5*5));
}


UNITTEST(Subgraph, GetSuperMap)
{
  GridGraphGenerator gen(5, 5, 5);

  ConstantGraph g = gen.generate();

  sl::Array<vtx_type> superMap(g.getNumVertices());
  sl::VectorMath::increment(superMap.data(), superMap.size(), 1U);

  Subgraph s(&g, &superMap);

  for (size_t i = 0; i < 5*5*5; ++i) {
    testEqual(s.getSuperMap()[i], static_cast<vtx_type>(i+1));
  }
}


UNITTEST(Subgraph, MapPartitioning)
{
  GridGraphGenerator gen(2,2,1);
  ConstantGraph tempG = gen.generate();

  sl::Array<vtx_type> superMap(tempG.getNumVertices());
  sl::VectorMath::increment(superMap.data(), superMap.size(), 0U);

  Subgraph s(&tempG, &superMap);

  ConstantGraph const * const g = s.getGraph();

  Partitioning subPart(2, g);
  subPart.assign(0, 0);
  subPart.assign(1, 0);
  subPart.assign(2, 1);
  subPart.assign(3, 1);

  sl::Array<pid_type> superLabels(g->getNumVertices());
  s.mapPartitioning(&subPart, superLabels.data(), 3);
  Partitioning superPart(5, g, &superLabels);

  testEqual(superPart.getAssignment(0), static_cast<pid_type>(3));
  testEqual(superPart.getAssignment(1), static_cast<pid_type>(3));
  testEqual(superPart.getAssignment(2), static_cast<pid_type>(4));
  testEqual(superPart.getAssignment(3), static_cast<pid_type>(4));
}


}
