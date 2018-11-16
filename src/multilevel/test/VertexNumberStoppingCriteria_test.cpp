/**
* @file VertexNumberStoppingCriteria_test.cpp
* @brief Unit tests for the VertexNumberStoppingCriteria class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-22
*/

#include "multilevel/VertexNumberStoppingCriteria.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"

namespace dolos
{

UNITTEST(VertexNumberStoppingCriteria, ShouldContinue)
{
  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  Graph coarse = genCoarse.generate();
  
  VertexNumberStoppingCriteria criteria(50);

  testFalse(criteria.shouldStop(0, nullptr, &coarse));
}

UNITTEST(VertexNumberStoppingCriteria, ShouldStop)
{
  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  Graph coarse = genCoarse.generate();
  
  VertexNumberStoppingCriteria criteria(64);

  testTrue(criteria.shouldStop(0, nullptr, &coarse));
}

}
