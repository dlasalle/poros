/**
* @file BitArray.hpp
* @brief The BitArray class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-20
*/




#ifndef DOLOS_SRC_BITARRAY_HPP
#define DOLOS_SRC_BITARRAY_HPP


#include <vector>

namespace dolos
{


class BitArray
{
  public:
    /**
    * @brief Create a new bit array.
    *
    * @param size The size to allocate.
    * @param initValue The value to fill it with.
    */
    BitArray(
        size_t const size,
        bool const initValue = false) :
      m_data(size, initValue)          
    {
      // do nothing
    }


    /**
    * @brief Make an index 'true'.
    *
    * @param index The index to mark.
    * @param value The value to mark the index with.
    */
    void mark(
        size_t const index,
        bool const value) noexcept
    {
      ASSERT_LESS(index, m_data.size());
      m_data[index] = value;
    }


    /**
    * @brief Flip an index in the array.
    *
    * @param index The index to flip.
    */
    void flip(
        size_t const index) noexcept
    {
      ASSERT_LESS(index, m_data.size());
      m_data[index] = !m_data[index];
    }


    /**
    * @brief Check an index of the array.
    *
    * @param index The index.
    *
    * @return True or false.
    */
    bool check(
        size_t const index) const noexcept
    {
      ASSERT_LESS(index, m_data.size());
      return m_data[index];
    }


    /**
    * @brief Clear the array.
    *
    * @param value The value to clear with.
    */
    void clear(
        bool const value = false) noexcept
    {
      m_data.reassign(m_data.size(), value);
    }

    private:
      std::vector<bool> m_data;
};

}

#endif
