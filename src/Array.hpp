/**
* @file Array.hpp
* @brief A mutable array structure for storing self-allocated or externally
* allocated memory.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-06
*/


#ifndef DOLOS_SRC_ARRAY_HPP
#define DOLOS_SRC_ARRAY_HPP


#include <cstring>
#include "Alloc.hpp"
#include "Debug.hpp"


namespace dolos
{

template<typename T>
class Array
{
  public:
    /**
    * @brief Create a new mutable array.
    *
    * @param size The size of the array.
    */
    Array(
        size_t const size) :
      m_size(size),
      m_data(Alloc::uninitialized<T>(size))
    {
      // do nothing
    }


    /**
    * @brief Copy constructor.
    *
    * @param lhs The array to copy.
    */
    Array(
        Array const & lhs) :
      m_size(lhs.m_size),
      m_data(Alloc::duplicate(lhs.m_data, lhs.m_size))
    {
      // do nothing
    }


    /**
    * @brief Move constructor.
    *
    * @param lhs The array to move.
    */
    Array(
        Array && lhs) :
      m_size(lhs.m_size),
      m_data(lhs.m_data)
    {
      lhs.m_size = 0;
      lhs.m_data = nullptr; 
    }


    /**
    * @brief The destructor.
    */
    ~Array()
    {
      Alloc::free(m_data);
    }


    /**
    * @brief Assignment operator (copy).
    *
    * @param lhs The array to assign to this one.
    *
    * @return This array.
    */
    Array & operator=(
        Array const & lhs)
    {
      m_size = lhs.m_size;
      Alloc::free(m_data);

      m_data = Alloc::duplicate(lhs.m_data, lhs.m_size);

      return this;
    }


    /**
    * @brief Assignment operator (move).
    *
    * @param lhs The array to assign (and destroy) to this one.
    *
    * @return This array.
    */
    Array & operator=(
        Array && lhs)
    {
      m_size = lhs.m_size;
      m_data = lhs.m_data;

      lhs.m_size = 0;
      lhs.m_data = nullptr;

      return this;
    }


    /**
    * @brief Set all entries in the array to the given value.
    *
    * @param val The value to set.
    */
    void set(
        T const val) noexcept
    {
      for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = val;
      }
    }


    /**
    * @brief Get the element at the given index.
    *
    * @param index The index of the element.
    *
    * @return A reference to the element.
    */
    T & operator[](
        size_t index) noexcept
    {
      ASSERT_LESS(index, m_size);
      return m_data[index];
    }


    /**
    * @brief Get the element at the given index.
    *
    * @param index The index of the element.
    *
    * @return A reference to the element.
    */
    T const & operator[](
        size_t index) const noexcept
    {
      ASSERT_LESS(index, m_size);
      return m_data[index];
    }


    /**
    * @brief Get the underlying memory.
    *
    * @return The underlying memory.
    */
    T * data() noexcept
    {
      return m_data;
    }


    /**
    * @brief Get the underlying memory.
    *
    * @return The underlying memory.
    */
    T const * data() const noexcept
    {
      return m_data;
    }


    /**
    * @brief Get the size of the underlying memory allocation.
    *
    * @return The size of the memory allocation.
    */
    size_t size() const noexcept
    {
      return m_size;
    }


  private:
    size_t m_size;
    T * m_data;


};

}



#endif
