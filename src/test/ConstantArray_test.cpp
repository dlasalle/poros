/**
* @file ConstantArray_test.cpp
* @brief Unit tests for the ConstantArray class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-06
*/


#include <vector>
#include "DomTest.hpp"
#include "ConstantArray.hpp"


namespace dolos
{


UNITTEST(ConstantArray, Size)
{
  std::vector<int> data{1,2,3,4,8}; 

  ConstantArray<int> c(data.size(), data.data());
  testEqual(c.size(), data.size());
}


UNITTEST(ConstantArray, SelfOwnerSize)
{
  int * data = reinterpret_cast<int*>(malloc(5UL));

  ConstantArray<int> c(5UL, data, true);

  testEqual(c.size(), 5UL);
}


UNITTEST(ConstantArray, ElementFetching)
{
  std::vector<int> data{1,2,3,4,8}; 

  ConstantArray<int> c(data.size(), data.data());
  testEqual(c.size(), data.size());

  for (size_t i = 0; i < data.size(); ++i) {
    testEqual(c[i], data[i]);
  }
}


UNITTEST(ConstantArray, MoveConstructor)
{
  std::vector<int> data{1,2,3,4,8}; 

  ConstantArray<int> c(data.size(), data.data());

  ConstantArray<int> b = std::move(c);

  testEqual(b.size(), data.size());

  for (size_t i = 0; i < data.size(); ++i) {
    testEqual(b[i], data[i]);
  }
}


UNITTEST(MutableArray, ExternalMutableConstructor)
{
  std::vector<int> data{1,2,3,4,8}; 
  MutableArray<int> m(data.size(), data.data());

  ConstantArray<int> c(std::move(m));
  testEqual(c.size(), data.size());

  for (size_t i = 0; i < c.size(); ++i) {
    testEqual(c[i], data[i]);
  }
}

UNITTEST(MutableArray, OwnerMutableConstructor)
{
  MutableArray<size_t> m(7UL);

  for (size_t i = 0; i < m.size(); ++i) {
    m[i] = 10UL - i;
  }

  ConstantArray<size_t> c(std::move(m));
  testEqual(7UL, c.size());

  for (size_t i = 0; i < c.size(); ++i) {
    testEqual(c[i], 10UL - i);
  }
}

}
