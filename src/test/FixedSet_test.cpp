/**
* @file FixedSet_test.cpp
* @brief Unit tests for the FixedSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-19
*/



#include "DomTest.hpp"
#include "FixedSet.hpp"


namespace dolos
{

UNITTEST(FixedSet, SizeAddRemove)
{
  FixedSet<int> set(10);

  testEqual(set.size(), 0);

  set.add(2);
  set.add(6);

  testEqual(set.size(), 2);

  set.remove(6);

  testEqual(set.size(), 1);

  set.remove(2);

  testEqual(set.size(), 0);
}

UNITTEST(FixedSet, HasAddRemove)
{
  FixedSet<int> set(10);

  testFalse(set.has(0));
  testFalse(set.has(2));
  testFalse(set.has(5));

  set.add(0);
  set.add(2);
  set.add(5);

  testTrue(set.has(0));
  testTrue(set.has(2));
  testTrue(set.has(5));

  set.remove(2);
  set.remove(5);

  testTrue(set.has(0));
  testFalse(set.has(2));
  testFalse(set.has(5));

  set.add(3);
  set.add(2);

  testTrue(set.has(0));
  testTrue(set.has(2));
  testTrue(set.has(3));

  set.remove(3);
  set.remove(0);
  set.remove(2);

  testFalse(set.has(0));
  testFalse(set.has(2));
  testFalse(set.has(3));
}


}
