/**
* @file EdgeRatioStoppingCriteria_test.cpp
* @brief Unit tests for the EdgeRatioStoppingCriteria class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-21
*/

#include "multilevel/EdgeRatioStoppingCriteria.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"

namespace poros
{

UNITTEST(EdgeRatioStoppingCriteria, ShouldContinue)
{
  // graph with 144 edges
  GridGraphGenerator genFine(4, 4, 4);
  Graph fine = genFine.generate();

  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  Graph coarse = genCoarse.generate();
  
  EdgeRatioStoppingCriteria criteria(0.8);

  testFalse(criteria.shouldStop(1, &fine, &coarse));
}

UNITTEST(EdgeRatioStoppingCriteria, ShouldStop)
{
  // graph with 144 edges
  GridGraphGenerator genFine(4, 4, 4);
  Graph fine = genFine.generate();

  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  Graph coarse = genCoarse.generate();
  
  EdgeRatioStoppingCriteria criteria(0.5);

  testTrue(criteria.shouldStop(1, &fine, &coarse));
}


UNITTEST(EdgeRatioStoppingCriteria, ZeroFine)
{
  // graph with 144 edges
  GridGraphGenerator genFine(1, 1, 1);
  Graph fine = genFine.generate();

  // graph with 108 edges
  GridGraphGenerator genCoarse(1, 1, 1);
  Graph coarse = genCoarse.generate();
  
  EdgeRatioStoppingCriteria criteria(0.75);

  testTrue(criteria.shouldStop(1, &fine, &coarse));
}

UNITTEST(EdgeRatioStoppingCriteria, NullFineContinue)
{
  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  Graph coarse = genCoarse.generate();
  
  EdgeRatioStoppingCriteria criteria(0.75);

  testFalse(criteria.shouldStop(0, nullptr, &coarse));
}

UNITTEST(EdgeRatioStoppingCriteria, NullFineStop)
{
  // graph with 108 edges
  GridGraphGenerator genCoarse(1, 1, 1);
  Graph coarse = genCoarse.generate();
  
  EdgeRatioStoppingCriteria criteria(0.75);

  testTrue(criteria.shouldStop(0, nullptr, &coarse));
}

}
