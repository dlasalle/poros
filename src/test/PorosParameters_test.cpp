/**
* @file PorosParameters_test.cpp
* @brief Unit tests for the PorosParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-09-04
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
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

