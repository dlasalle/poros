/**
* @file TargetPartitioning.cpp
* @brief Unit tests for TargetPartitioning class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-11-03
*/



#include "TargetPartitioning.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>

namespace dolos
{


UNITTEST(TargetPartitioning, GetMaxWeight)
{
  TargetPartitioning target(2, 200, 0.03); 

  testEqual(target.getMaxWeight(0), 103u);
  testEqual(target.getMaxWeight(1), 103u);

  testEqual(target.getMaxWeight()[0], 103u);
  testEqual(target.getMaxWeight()[1], 103u);
}


UNITTEST(TargetPartitioning, GetTargetWeight)
{
  TargetPartitioning target(2, 200, 0.03); 

  testEqual(target.getTargetWeight(0), 100u);
  testEqual(target.getTargetWeight(1), 100u);

  testEqual(target.getTargetWeight()[0], 100u);
  testEqual(target.getTargetWeight()[1], 100u);
}

UNITTEST(TargetPartitioning, GetMaxWeightFractions)
{
  std::vector<double> fractions{0.3, 0.3, 0.4};
  TargetPartitioning target(fractions.size(), 100, 0.05, fractions.data()); 

  testEqual(target.getMaxWeight(0), 31u);
  testEqual(target.getMaxWeight(1), 31u);
  testEqual(target.getMaxWeight(2), 42u);

  testEqual(target.getMaxWeight()[0], 31u);
  testEqual(target.getMaxWeight()[1], 31u);
  testEqual(target.getMaxWeight()[2], 42u);
}


UNITTEST(TargetPartitioning, GetTargetWeightFractions)
{
  std::vector<double> fractions{0.3, 0.3, 0.4};
  TargetPartitioning target(fractions.size(), 100, 0.05, fractions.data()); 

  testEqual(target.getTargetWeight(0), 30u);
  testEqual(target.getTargetWeight(1), 30u);
  testEqual(target.getTargetWeight(2), 40u);

  testEqual(target.getTargetWeight()[0], 30u);
  testEqual(target.getTargetWeight()[1], 30u);
  testEqual(target.getTargetWeight()[2], 40u);

}




}
