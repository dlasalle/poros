/**
* @file MutableArray_test.hpp
* @brief Unit tests for the MutableArray class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-06
*/


#include "DomTest.hpp"
#include "MutableArray.hpp"


namespace dolos
{


UNITTEST(MutableArray, ExternalSize)
{
  std::vector<int> data{1,2,3,4,8}; 

  MutableArray m(data.size(), data.data());
  assertEqual(m.size(), data.size());
}


UNITTEST(MutableArray, OwnerSize)
{
  MutableArray m(5UL);

  assertEqual(m.size(), 5UL);
}


UNITTEST(MutableArray, ExternalElementFetching)
{
  std::vector<int> data{1,2,3,4,8}; 
  MutableArray m(data.size(), data.data());

  for (size_t i = 0; i < data.size(); ++i) {
    assertEqual(m[i], data[i]);
  }
}


UNITTEST(MutableArray, OwnerElementFetching)
{
  MutableArray m(5UL);

  for (size_t i = 0; i < m.size(); ++i) {
    m[i] = 10UL - i;
  }

  for (size_t i = 0; i < m.size(); ++i) {
    assertEqual(m[i], 10UL - i);
  }
}


UNITTEST(MutableArray, ExternalFinalize)
{
  std::vector<int> data{1,2,3,4,8}; 
  MutableArray m(data.size(), data.data());

  ConstantArray c = m.finalize();
  assertEqual(m.size(), c.size());

  for (size_t i = 0; i < c.size(); ++i) {
    assertEqual(c[i], m[i]);
  }
}

UNITTEST(MutableArray, OwnerFinalize)
{
  MutableArray m(data.size(), 7UL);

  for (size_t i = 0; i < m.size(); ++i) {
    m[i] = 10UL - i;
  }

  ConstantArray c = m.finalize();
  assertEqual(m.size(), c.size());

  for (size_t i = 0; i < c.size(); ++i) {
    assertEqual(c[i], m[i]);
  }
}

}
