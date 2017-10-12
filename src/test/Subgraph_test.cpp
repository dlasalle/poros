/**
* @file Subgraph_test.cpp
* @brief Unit tests for the Subgraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-12
*/

#include "DomTest.hpp"
#include "Subgraph.hpp"
#include "ConstantGraph.hpp"
#include "GridGraphGenerator.hpp"
#include "ArrayUtils.hpp"
#include "Array.hpp"


namespace dolos
{


UNITTEST(Subgraph, GetGraph)
{
  GridGraphGenerator gen(5, 5, 5);

  ConstantGraph g = gen.generate();

  Array<vtx_type> superMap(g.getNumVertices());
  ArrayUtils::increment(&superMap, 1U);

  Subgraph s(&g, &superMap);

  testEqual(s.getGraph()->getNumVertices(), 5*5*5);
}


UNITTEST(Subgraph, GetSuperMap)
{
  GridGraphGenerator gen(5, 5, 5);

  ConstantGraph g = gen.generate();

  Array<vtx_type> superMap(g.getNumVertices());
  ArrayUtils::increment(&superMap, 1U);

  Subgraph s(&g, &superMap);

  for (size_t i = 0; i < 5*5*5; ++i) {
    testEqual(s.getSuperMap()[i], static_cast<vtx_type>(i+1));
  }
}


}
