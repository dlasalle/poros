/**
* @file ArrayUtils.hpp
* @brief Utility functions for arrays of specific types.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-11
*/



#ifndef DOLOS_SRC_ARRAYUTILS_HPP
#define DOLOS_SRC_ARRAYUTILS_HPP


#include "Array.hpp"


namespace dolos
{


class ArrayUtils
{
  public:
    /**
    * @brief Set all entries int the array to the given sequence.
    *
    * @tparam The type of elements in the array.
    * @param start The starting value of the sequence.
    * @param inc The increment of the sequence.
    */
    template <typename T>
    static void increment(
        Array<T> * const array,
        T const start,
        T const inc = 1) noexcept
    {
      T val = start;
      size_t const size = array.size();
      for (size_t i = 0; i < size; ++i) {
        array[i] = val;
        val += inc;
      }
    }


    /**
    * @brief Perform a prefix sum on an array.
    *
    * @tparam T The type of elements in the array.
    * @param array The array to prefixsum.
    */
    template <typename T>
    static void prefixSumExclusive(
        Array<T> * const array) noexcept
    {
      size_t const size = array->size();

      T sum = 0;
      for (size_t i = 0; i < size; ++i) {
        T const val = (*array)[i];
        (*array)[i] = sum;
        sum += val;
      }
    }


};


}



#endif
