/**
* @file PartitionParameters_test.cpp
* @brief Unit tests for the PartitionParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-11
*/


#include <vector>
#include <cstdlib>
#include "solidutils/UnitTest.hpp"
#include "PartitionParameters.hpp"


namespace dolos
{


UNITTEST(BisectionParameters, SetGetTolerance)
{
  PartitionParameters params(2);
  params.setImbalanceTolerance(0.015);

  testEqual(params.getImbalanceTolerance(), 0.015);
}


UNITTEST(BisectionParameters, SetGetTargetFractions)
{
  std::vector<double> targets{0.3, 0.5, 0.2};

  PartitionParameters params(targets.size());
  params.setTargetPartitionFractions(targets.data());

  double const * testTargets = params.getTargetPartitionFractions();

  for (size_t i = 0; i < targets.size(); ++i) {
    testEqual(testTargets[i], targets[i]);
  }
}


}
