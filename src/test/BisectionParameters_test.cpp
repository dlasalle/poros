/**
* @file BisectionParameters_test.cpp
* @brief Unit tests for the BisectionParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/


#include <vector>
#include <cstdlib>
#include "DomTest.hpp"
#include "BisectionParameters.hpp"


namespace dolos
{


UNITTEST(BisectionParameters, SetGet)
{
  BisectionParameters params;
  params.setLeftSideTarget(0.4);
  params.setImbalanceTolerance(0.015);

  testEqual(params.getImbalanceTolerance(), 0.015);
  testEqual(params.getLeftSideTarget(), 0.4);
  testEqual(params.getRightSideTarget(), 0.6);

  testEqual(params.getLeftSideMax(), 0.4*0.15);
  testEqual(params.getRightSideTarget() 0.6*0.15);
}


}
