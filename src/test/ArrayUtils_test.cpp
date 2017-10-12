/**
* @file ArrayUtils_test.cpp
* @brief Unit tests for the ArrayUtils class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-11
*/



#include "ArrayUtils.hpp"
#include "Array.hpp"
#include "DomTest.hpp"



namespace dolos
{


UNITTEST(ArrayUtils, Increment)
{
  Array<int> m(5UL);

  ArrayUtils::increment(&m, 1, 2);

  int val = 1;
  for (size_t i = 0; i < m.size(); ++i) {
    testEqual(m[i], val);
    val += 2;
  }
}


UNITTEST(Array, PrefixSumExclusive)
{
  Array<size_t> m(3UL);

  m[0] = 3;
  m[1] = 1;
  m[2] = 2;

  ArrayUtils::prefixSumExclusive(&m);

  testEqual(m[0], 0);
  testEqual(m[1], 3);
  testEqual(m[2], 4);
}





}
