/**
* @file ConstantArray_test.hpp
* @brief Unit tests for the ConstantArray class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-06
*/


#include "DomTest.hpp"
#include "ConstantArray.hpp"


namespace dolos
{


UNITTEST(ConstantArray, Size)
{
  std::vector<int> data{1,2,3,4,8}; 

  ConstantArray c(data.size(), data.data());
  assertEqual(c.size(), data.size());
}


UNITTEST(ConstantArray, SelfOwnerSize)
{
  int * data = malloc(5UL);

  ConstantArray c(5UL, data, true);

  assertEqual(c.size(), 5UL);
}


UNITTEST(ConstantArray, ElementFetching)
{
  std::vector<int> data{1,2,3,4,8}; 

  ConstantArray c(data.size(), data.data());

  for (size_t i = 0; i < data.size(); ++i) {
    assertEqual(c[i], data[i]);
  }
}


}
