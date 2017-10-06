/**
* @file RandomTraverser_test.cpp
* @brief Unit tests for the RandomTraverser class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-06
*/


#include "DomTest.hpp"
#include "RandomTraverser.hpp"


namespace dolos
{


UNITTEST(RandomTraverser, Next)
{
  RandomTraverser r(10);

  size_t steps = 0;
  while (r.next()) {
    ++steps;
  }

  testEqual(steps, 10);
}

UNITTEST(RandomTraverser, GetCompleteness)
{
  std::vector<bool> mark(50, false);

  RandomTraverser r(mark.size());

  // make sure every location is marked exactly once

  while (r.next()) {
    testFalse(mark[r.get()]);
    mark[r.get()] = true;
  }

  for (bool const & marked : mark) {
    testTrue(marked);
  }
}

UNITTEST(RandomTraverser, GetRandomness)
{
  RandomTraverser r1(100);
  RandomTraverser r2(100);

  // we rely on the probability to randomly shuffling two arrays of sufficient
  // size should very rarely result in identical permutations.
  size_t commons = 0;
  while (r1.next() && r2.next()) {
    if (r1.get() == r2.get()) {
      ++commons;
    }
  }

  testLess(commons, 100);
}


}
