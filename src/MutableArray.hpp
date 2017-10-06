/**
* @file MutableArray.hpp
* @brief A mutable array structure for storing self-allocated or externally
* allocated memory.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-06
*/


#ifndef DOLOS_SRC_MUTABLEARRAY_HPP
#define DOLOS_SRC_MUTABLEARRAY_HPP


#include <cstring>
#include "Debug.hpp"
#include "ConstantArray.hpp"


namespace dolos
{

template<typename T>
class MutableArray
{
  public:
    /**
    * @brief Create a new mutable array.
    *
    * @param size The size of the array.
    * @param data The allocated memory for the array (if null, memory will be
    * allocated but uninitialized.
    */
    MutableArray(
        size_t size,
        T * data = nullptr) :
      m_owner(false),
      m_size(size),
      m_data(data)
    {
      if (size == 0) {
        // always allocate one element
        size = 1;
      }

      if (data == nullptr) {
        m_owner = true;
        m_data = malloc(sizeof(T)*size);
      }
    }


    /**
    * @brief The destructor.
    */
    ~MutableArray()
    {
      if (m_owner) {
        free(m_data);
      }
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
      m_data = nullptr;
      m_size = 0;
    }


    /**
    * @brief Create a constant version of this array and destroy this one.
    * Calling any method other than the destructor is undefined behavior after
    * this method.
    *
    * @return The finalized version of this array.
    */
    ConstantArray<T> finalize()
    {
      // make sure we haven't been finalized yet
      ASSERT_FALSE(!m_owner && !m_data && !m_size);

      // only give ownership to the constant version if we currently have
      // ownership
      ConstantArray<T> finalArray(m_size, m_data, m_owner);

      // make this array useless
      disown();

      // NRVO -- the object will be returned in place rather than copied
      return finalArray;
    }


    /**
    * @brief Get the element at the given index. If a constant version of this
    * method is needed, the object should be converted to a ConstantArray.
    *
    * @param index The index of the element.
    *
    * @return A reference to the element.
    */
    T & operator[](
        size_t index) noexcept
    {
      ASSERT_FALSE(!m_owner && !m_data && !m_size);
      ASSERT_LESS(index, m_size);
      return m_data[index];
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
      ASSERT_FALSE(!m_owner && !m_data && !m_size);
      return m_size;
    }


  private:
    bool m_owner;
    size_t m_size;
    T * m_data;
};

}



#endif
