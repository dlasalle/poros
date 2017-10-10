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
#include "IBisector.hpp"


namespace dolos
{


UNITTEST(BisectionParameters, SetGet)
{
  std::vector<double> targets{0.4, 0.6};

  BisectionParameters params;
  params.setTargetFractions(targets.data());
  params.setImbalanceTolerance(0.015);

  testEqual(params.getImbalanceTolerance(), 0.015);

  double const * testTargets = params.getTargetFractions();
  double const * testMaxs = params.getMaxFractions();

  for (size_t i = 0; i < NUM_BISECTION_PARTS; ++i) {
    testEqual(testTargets[i], targets[i]);
    testEqual(testMaxs[i], targets[i]*1.015);
  }
}


}
