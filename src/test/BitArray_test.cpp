/**
* @file BitArray_test.cpp
* @brief Unit tests for the BitArray class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-20
*/


#include "DomTest.hpp"
#include "BitArray.hpp"


namespace dolos
{

UNITTEST(BitArray, Size)
{
  BitArray ba(100);

  testEqual(ba.size(), 100);
}



UNITTEST(BitArray, MarkCheck)
{
  BitArray ba(100);

  // make sure it starts out false
  for (size_t i = 0; i < ba.size(); ++i) {
    testFalse(ba.check(i));
  }

  for (size_t i = 0; i < ba.size(); ++i) {
    if (i % 7 == 0) {
      ba.mark(i);
    }
  }

  for (size_t i = 0; i < ba.size(); ++i) {
    if (i % 7 == 0) {
      testTrue(ba.check(i));
    } else {
      testFalse(ba.check(i));
    }
  }
}

UNITTEST(BitArray, FlipCheck)
{
  BitArray ba(100);

  // make sure it starts out false
  for (size_t i = 0; i < ba.size(); ++i) {
    testFalse(ba.check(i));
  }

  for (size_t i = 0; i < ba.size(); ++i) {
    if (i % 9 == 0) {
      ba.flip(i);
    }
  }

  for (size_t i = 0; i < ba.size(); ++i) {
    if (i % 9 == 0) {
      testTrue(ba.check(i));
    } else {
      testFalse(ba.check(i));
    }
  }

  for (size_t i = 0; i < ba.size(); ++i) {
    if (i % 3 == 0) {
      ba.flip(i);
    }
  }

  for (size_t i = 0; i < ba.size(); ++i) {
    if (i % 3 == 0) {
      if (i % 9 == 0) {
        testFalse(ba.check(i));
      } else {
        testTrue(ba.check(i));
      }
    } else {
      testFalse(ba.check(i));
    }
  }
}

UNITTEST(BitArray, ClearFalse)
{
   BitArray ba(100);

  for (size_t i = 0; i < ba.size(); ++i) {
    if (i % 7 == 0) {
      ba.mark(i);
    }
  }

  ba.clear();

  // make sure it starts out false
  for (size_t i = 0; i < ba.size(); ++i) {
    testFalse(ba.check(i));
  }
}

UNITTEST(BitArray, ClearTrue)
{
   BitArray ba(100);

  for (size_t i = 0; i < ba.size(); ++i) {
    if (i % 7 == 0) {
      ba.mark(i);
    }
  }

  ba.clear(true);

  // make sure it starts out false
  for (size_t i = 0; i < ba.size(); ++i) {
    testTrue(ba.check(i));
  }
}

}
