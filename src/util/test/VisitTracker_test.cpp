/**
* @file VisitTracker_test.cpp
* @brief Unit tests for the VisitTracker class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-24
*/


#include "util/VisitTracker.hpp"

#include "solidutils/UnitTest.hpp"

namespace dolos
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
