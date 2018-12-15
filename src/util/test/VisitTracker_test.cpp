/**
* @file VisitTracker_test.cpp
* @brief Unit tests for the VisitTracker class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-24
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


#include "util/VisitTracker.hpp"

#include "solidutils/UnitTest.hpp"

namespace poros
{


UNITTEST(VisitTracker, HasVisitedNone)
{
  VisitTracker tracker(15);

  for (size_t i = 0; i < tracker.size(); ++i) {
    testFalse(tracker.hasVisited(i));
  }
}

UNITTEST(VisitTracker, HasVisitedSome)
{
  VisitTracker tracker(15);

  tracker.visit(5);
  tracker.visit(6);
  tracker.visit(10);
  tracker.visit(13);

  for (size_t i = 0; i < tracker.size(); ++i) {
    if (i == 5 || i == 6 || i == 10 || i == 13) {
      testTrue(tracker.hasVisited(i));
    } else {
      testFalse(tracker.hasVisited(i));
    }
  }
}

}
