/**
* @file RandomEngineFactory_test.cpp
* @brief Unit tests for teh RandomEngineFactory class.
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

#include "util/RandomEngineFactory.hpp"

#include "solidutils/UnitTest.hpp"


namespace poros
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

