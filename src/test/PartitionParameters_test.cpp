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
#include "DomTest.hpp"
#include "PartitionParameters.hpp"


namespace dolos
{


UNITTEST(BisectionParameters, SetGet)
{
  std::vector<double> targets{0.3, 0.5, 0.2};

  PartitionParameters params(targets.size());
  params.setTargetPartitionFractions(targets.data());
  params.setImbalanceTolerance(0.015);

  testEqual(params.getImbalanceTolerance(), 0.015);

  double const * testTargets = params.getTargetPartitionFractions();
  double const * testMaxs = params.getMaxPartitionFractions();

  for (size_t i = 0; i < targets.size(); ++i) {
    testEqual(testTargets[i], targets[i]);
    testEqual(testMaxs[i], targets[i]*1.015);
  }
}


}
