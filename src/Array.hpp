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
    * @brief Create a new mutable array with a default value for each element.
    *
    * @param size The size of the array.
    */
    Array(
        size_t const size,
        T const value) :
      m_size(size),
      m_data(Alloc::initialized<T>(size, value))
    {
      // do nothing
    }


    /**
    * @brief Move constructor.
    *
    * @param lhs The array to move.
    */
    Array(
        Array && lhs) noexcept :
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

      return *this;
    }


    /**
    * @brief Resize the array.
    *
    * @param size The new size.
    */
    void resize(
        size_t const size)
    {
      if (m_size > 0) {
        // actually resize
        m_size = size;
        Alloc::resize<T>(&m_data, size);
      } else {
        // initialize allocation
        m_size = size;
        m_data = Alloc::uninitialized<T>(size);
      }
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
        size_t const index) noexcept
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
        size_t const index) const noexcept
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


    /**
    * @brief Get the beginning iterator.
    *
    * @return The iterator/pointer.
    */
    T * begin() const noexcept
    {
      return m_data;
    }


    /**
    * @brief Get the end iterator.
    *
    * @return The iterator/pointer.
    */
    T * end() const noexcept
    {
      return m_data + m_size;
    }


  private:
    size_t m_size;
    T * m_data;

    // disable copying
    Array(
        Array const & lhs);
    Array & operator=(
        Array const & lhs);


};

}



#endif
