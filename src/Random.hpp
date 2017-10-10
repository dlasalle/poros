/**
* @file Random.hpp
* @brief The Random class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/





#ifndef DOLOS_SRC_RANDOM_HPP
#define DOLOS_SRC_RANDOM_HPP


#include <cstdlib>
#include "Debug.hpp"


namespace dolos
{

class Random
{
  public:
    /**
    * @brief Get a single random number in a specified range (inclusive). If
    * min is greater than max, the behavior is undefined (very bad).
    *
    * @tparam T The type of number to get.
    * @param min The minimum value (inclusive).
    * @param max The maximum value (inclusive).
    */
    template <typename T>
    inline static T inRange(
        T const min,
        T const max) noexcept
    {
      ASSERT_LESSEQUAL(min, max);

      T const range = (max+1) - min;
      T const entropy = std::rand() % range;

      return entropy + min;
    }

    /**
    * @brief Fill a location in memory with random numbers. If min and max are
    * the same, an optimization is used where random is never called. If min is
    * greater than max, the behavior is undefined (very bad).
    *
    * @tparam T The type of number to fill with.
    * @param data The memory location.
    * @param num The number of elements to insert.
    * @param min The minimum number.
    * @param max The maximum number.
    */
    template <typename T>
    inline static void fillWithRange(
        T * const data,
        size_t const num,
        T const min,
        T const max) noexcept
    {
      if (min == max) {
        for (size_t i = 0; i < num; ++i) {
          data[i] = min;
        }
      } else {
        for (size_t i = 0; i < num; ++i) {
          data[i] = inRange(min, max);
        }
      }
    }



};


}


#endif
