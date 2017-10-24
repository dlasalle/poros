/**
* @file FixedSet.hpp
* @brief The FixedSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-19
*/



#ifndef DOLOS_SRC_FIXEDSET_HPP
#define DOLOS_SRC_FIXEDSET_HPP


#include "Array.hpp"


namespace dolos
{


template <typename T>
class FixedSet
{
  public:
    static constexpr T const NULL_INDEX = static_cast<T>(-1);

    /**
    * @brief Create a new empty fixed set.
    *
    * @param size The size of the set.
    */
    FixedSet(
        size_t const size) :
      m_size(0),
      m_data(size),
      m_index(size, NULL_INDEX)
    {
      // do nothing
    }


    /**
    * @brief Check if an element exists in this set.
    *
    * @param element The element.
    *
    * @return The element. 
    */
    bool has(
        T const element) const noexcept
    {
      size_t const index = static_cast<size_t>(element);

      ASSERT_LESS(index, m_index.size());

      return m_index[index] != NULL_INDEX; 
    }

    /**
    * @brief Add an element to this set.
    *
    * @param element The element to add.
    */
    void add(
        T const element) noexcept
    {
      size_t const index = static_cast<size_t>(element);

      ASSERT_LESS(index, m_index.size());
      ASSERT_EQUAL(m_index[index], NULL_INDEX);

      m_data[m_size] = element; 
      m_index[index] = m_size;

      ++m_size;
    }
     

    /**
    * @brief Remove an element from this set.
    *
    * @param element The element to remove.
    */
    void remove(
        T const element) noexcept
    {
      size_t const index = static_cast<size_t>(element);

      ASSERT_LESS(index, m_index.size());
      ASSERT_NOTEQUAL(m_index[index], NULL_INDEX);

      --m_size;
      T const swap = m_data[m_size];
      size_t const place = m_index[index];       
      m_data[place] = swap;
      m_index[swap] = index;
      m_index[index] = NULL_INDEX;
    }


    /**
    * @brief Get the underlying array.
    *
    * @return The data.
    */
    T * data() noexcept
    {
      return m_data.data();
    }


    /**
    * @brief Get the underlying array.
    *
    * @return The data.
    */
    T const * data() const noexcept
    {
      return m_data.data();
    }


    /**
    * @brief Get the number of elements in the set.
    *
    * @return The number of elements.
    */
    size_t size() const noexcept
    {
      return m_size;
    }


  private: 
    size_t m_size;
    Array<T> m_data;
    Array<T> m_index;
};

}

#endif
