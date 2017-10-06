/**
* @file MutableArray_test.cpp
* @brief Unit tests for the MutableArray class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-06
*/


#include <vector>
#include <cstdlib>
#include "DomTest.hpp"
#include "MutableArray.hpp"


namespace dolos
{


UNITTEST(MutableArray, ExternalSize)
{
  std::vector<int> data{1,2,3,4,8}; 

  MutableArray<int> m(data.size(), data.data());
  testEqual(m.size(), data.size());
}


UNITTEST(MutableArray, OwnerSize)
{
  MutableArray<int> m(5UL);

  testEqual(m.size(), 5UL);
}


UNITTEST(MutableArray, ExternalElementFetching)
{
  std::vector<int> data{1,2,3,4,8}; 
  MutableArray<int> m(data.size(), data.data());

  for (size_t i = 0; i < data.size(); ++i) {
    testEqual(m[i], data[i]);
  }
}


UNITTEST(MutableArray, OwnerElementFetching)
{
  MutableArray<size_t> m(5UL);

  for (size_t i = 0; i < m.size(); ++i) {
    m[i] = 10UL - i;
  }

  for (size_t i = 0; i < m.size(); ++i) {
    testEqual(m[i], 10UL - i);
  }
}


UNITTEST(MutableArray, ExternalFinalize)
{
  std::vector<int> data{1,2,3,4,8}; 
  MutableArray<int> m(data.size(), data.data());

  ConstantArray<int> c = m.finalize();
  testEqual(c.size(), data.size());

  for (size_t i = 0; i < c.size(); ++i) {
    testEqual(c[i], data[i]);
  }
}

UNITTEST(MutableArray, OwnerFinalize)
{
  MutableArray<size_t> m(7UL);

  for (size_t i = 0; i < m.size(); ++i) {
    m[i] = 10UL - i;
  }

  ConstantArray<size_t> c = m.finalize();
  testEqual(m.size(), c.size());

  for (size_t i = 0; i < c.size(); ++i) {
    testEqual(c[i], m[i]);
  }
}

}
