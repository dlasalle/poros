/**
* @file RandomEngineFactory_test.cpp
* @brief Unit tests for teh RandomEngineFactory class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-09-04
*/

#include "util/RandomEngineFactory.hpp"

#include "solidutils/UnitTest.hpp"


namespace dolos
{

UNITTEST(RandomEngineFactory, SameSeedTest)
{
  RandomEngineHandle handle1 = RandomEngineFactory::make(1234);
  RandomEngineHandle handle2 = RandomEngineFactory::make(1234);

  for (size_t i = 0; i < 1000; ++i) {
    testEqual(handle1.randInRange(0, 10000), handle2.randInRange(0, 10000));
  }
}


UNITTEST(RandomEngineFactory, DifferentSeedTest)
{
  RandomEngineHandle handle1 = RandomEngineFactory::make(1234);
  RandomEngineHandle handle2 = RandomEngineFactory::make(1233);

  int differences = 0;
  for (size_t i = 0; i < 1000; ++i) {
    if (handle1.randInRange(0, 10000) != handle2.randInRange(0, 10000)) {
      ++differences;
    }
  }

  // expect at least 99.0% different
  testGreater(differences, 990);
}

}

