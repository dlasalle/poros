/**
* @file PorosParameters_test.cpp
* @brief Unit tests for the PorosParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-09-04
*/

#include "PorosParameters.hpp"
#include "solidutils/UnitTest.hpp"

namespace poros
{

UNITTEST(PorosParameters, ConsistentRandomSeed)
{
  poros_options_struct opts{};

  opts.randomSeed = 1970;

  PorosParameters params1(opts);
  PorosParameters params2(opts);

  RandomEngineHandle engine1 = params1.randomEngine();
  RandomEngineHandle engine2 = params2.randomEngine();

  for (size_t i = 0; i < 1000; ++i) {
    testEqual(engine1.randInRange(0, 10000), engine2.randInRange(0, 10000));
  }
}


UNITTEST(PorosParameters, DifferentRandomSeed)
{
  poros_options_struct opts{};

  opts.randomSeed = 1970;
  PorosParameters params1(opts);

  opts.randomSeed = 0;
  PorosParameters params2(opts);

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

