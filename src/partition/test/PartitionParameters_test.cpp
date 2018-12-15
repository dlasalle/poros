/**
* @file PartitionParameters_test.cpp
* @brief Unit tests for the PartitionParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-11
*/


#include "partition/PartitionParameters.hpp"
#include "solidutils/UnitTest.hpp"

#include <vector>
#include <cstdlib>


namespace poros
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
