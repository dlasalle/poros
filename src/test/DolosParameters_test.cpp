/**
* @file DolosParameters_test.cpp
* @brief Unit tests for the DolosParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-09-04
*/

#include "DolosParameters.hpp"
#include "solidutils/UnitTest.hpp"

namespace dolos
{

UNITTEST(DolosParameters, ConsistentRandomSeed)
{
  dolos_options_struct opts{};

  opts.randomSeed = 1970;

  DolosParameters params1(&opts);
  DolosParameters params2(&opts);

  RandomEngineHandle engine1 = params1.randomEngine();
  RandomEngineHandle engine2 = params2.randomEngine();

  for (size_t i = 0; i < 1000; ++i) {
    testEqual(engine1.randInRange(0, 10000), engine2.randInRange(0, 10000));
  }
}


UNITTEST(DolosParameters, DifferentRandomSeed)
{
  dolos_options_struct opts{};

  opts.randomSeed = 1970;
  DolosParameters params1(&opts);

  opts.randomSeed = 0;
  DolosParameters params2(&opts);

  RandomEngineHandle engine1 = params1.randomEngine();
  RandomEngineHandle engine2 = params2.randomEngine();

  int differences = 0;
  for (size_t i = 0; i < 1000; ++i) {
    if (engine1.randInRange(0, 10000) != engine2.randInRange(0, 10000)) {
      ++differences;
    }
  }

  testGreater(differences, 990);
}

}

