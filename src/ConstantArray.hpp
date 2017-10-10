/**
* @file ConstantArray.hpp
* @brief A constant array structure for storing self-allocated or externally
* allocated memory.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2017-10-06
*/



#ifndef DOLOS_SRC_CONSTANTARRAY_HPP
#define DOLOS_SRC_CONSTANTARRAY_HPP


#include <cstring>
#include "Debug.hpp"
#include "MutableArray.hpp"


namespace dolos
{

template<typename T>
class ConstantArray
{
  public:
    /**
    * @brief Create a new constant array.
    *
    * @param size The size of the array.
    * @param data The allocated memory for the array.
    * @param owner Whether or not this object should own the memory passed in.
    */
    ConstantArray(
        size_t size,
        T const * const data,
        bool owner = false) :
      m_owner(owner),
      m_size(size),
      m_data(data)
    {
      // do nothing
    }


    /**
    * @brief Create a new constant array.
    *
    * @param size The size of the array.
    * @param value The value to fill with. 
    */
    ConstantArray(
        size_t size,
        T const value) :
      m_owner(true),
      m_size(size),
      m_data(nullptr)
    {
      T * const data = reinterpret_cast<T>(malloc(sizeof(T)*size));
      for (size_t i = 0; i < m_size; ++i) {
        data[i] = value;
      }

      m_data = data;
    }


    /**
    * @brief Move constructor.
    *
    * @param lhs The array to move.
    */
    ConstantArray(
        ConstantArray<T> && lhs) noexcept :
      m_owner(lhs.m_owner),
      m_size(lhs.m_size),
      m_data(lhs.m_data)
    {
      ASSERT_FALSE(!lhs.m_owner && !lhs.m_data && !lhs.m_size);

      lhs.m_owner = false;
      lhs.m_size = 0;
      lhs.m_data = nullptr;
    }


    /**
    * @brief Move constructor.
    *
    * @param lhs The mutable array to convert.
    */
    ConstantArray(
        MutableArray<T> && lhs) noexcept :
      m_owner(lhs.isOwner()),
      m_size(lhs.size()),
      m_data(lhs.data())
    {
      ASSERT_FALSE(!m_owner && !m_data && !m_size);

      lhs.disown();
    }


    /**
    * @brief The destructor.
    */
    ~ConstantArray()
    {
      if (m_owner) {
        free(m_data);
      }
    }


    /**
    * @brief Move assignment operator.
    *
    * @param lhs The array on the left hand side of the equals.
    */
    ConstantArray & operator=(
        ConstantArray<T> && lhs) noexcept
    {
      ASSERT_FALSE(!lhs.m_owner && !lhs.m_data && !lhs.m_size);

      m_owner = lhs.m_owner;
      m_size = lhs.m_size;
      m_data = lhs.m_data;

      lhs.m_owner = false;
      lhs.m_size = 0;
      lhs.m_data = nullptr;
    }


    /**
    * @brief Move assignment operator.
    *
    * @param lhs The array on the left hand side of the equals.
    */
    ConstantArray & operator=(
        MutableArray<T> && lhs) noexcept
    {
      m_owner = lhs.isOwner();
      m_size = lhs.size();
      m_data = lhs.data();

      ASSERT_FALSE(!m_owner && !m_data && !m_size);

      lhs.m_owner = false;
      lhs.m_size = 0;
      lhs.m_data = nullptr;
    }


    /**
    * @brief Give up the contents of this array. It becomes useless after this
    * operation, and calling anything other than the destructor is considered
    * undefined behavior.
    */
    void disown()
    {
      // make sure we haven't been finalized yet
      ASSERT_FALSE(!m_owner && !m_data && !m_size);

      // make this array useless
      m_owner = false;
      m_size = 0;
      m_data = nullptr;
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
    * @brief Check if this array owns its memory.
    *
    * @return 
    */
    bool isOwner() noexcept
    {
      ASSERT_FALSE(!m_owner && !m_data && !m_size);

      return m_owner;
    }


    /**
    * @brief Get the underlying array.
    *
    * @return The underlying array.
    */
    T * data() noexcept
    {
      return m_data;
    }


    /**
    * @brief Get the size of the underlying memory allocation.
    *
    * @return The size of the memory allocation.
    */
    size_t size() const noexcept {
      return m_size;
    }


  private:
    bool m_owner;
    size_t m_size;
    T const * m_data;

    // disable copying
    ConstantArray(
        ConstantArray<T> const & lhs);
    ConstantArray<T> & operator=(
        ConstantArray<T> const & lhs);

};

}

#endif
