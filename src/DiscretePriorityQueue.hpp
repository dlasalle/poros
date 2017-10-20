/**
* @file FixedPriorityQueue.hpp
* @brief The FixedPriorityQueue class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-20
*/




#ifndef DOLOS_SRC_FIXEDPRIORITYQUEUE_HPP
#define DOLOS_SRC_FIXEDPRIORITYQUEUE_HPP

#include "Array.hpp"

namespace dolos
{


template<typename K, typename V>
class FixedPriorityQueue
{
  public:
    static constexpr size_t const NULL_INDEX = static_cast<size_t>(-1);

    FixedPriorityQeueu(
        V const min,
        V const max) :
      m_min(min),
      m_max(max),
      m_data(max-min),
      m_index(max-min, NULL_INDEX),
      m_size(0)
    {
      ASSERT_LESS(min, max);

      
    }


    /**
    * @brief Remove an element from the queue.
    *
    * @param elem The element to remove
    */
    void remove(
        V const value) noexcept
    {
      ASSERT_LESS(value, m_index.size());
      ASSERT_NOTEQUAL(m_index[value], NULL_INDEX);

      // remove item from heap and sort up
      size_t const index = m_index[value];
      m_index[value] = NULL_INDEX;
      fill(index);
    }


    /**
    * @brief Add an value to the queue.
    *
    * @param key The key/priority of the value to add.
    * @param value The value to add.
    */
    void add(
        K const key,
        V const value) noexcept
    {
      ASSERT_LESS(value, m_index.size());
      ASSERT_EQUAL(m_index[value], NULL_INDEX);

      size_t const index = m_size++;
      m_index[value] = index;
      m_data[index].key = key;
      m_data[index].value = value;

      place(index);
    }


    /**
    * @brief Pop the top value from the queue.
    *
    * @return The top value.
    */
    V pop() noexcept
    {
      ASSERT_GREATER(m_index.size(), 0);

      V const value = m_data[0].value;
      fill(0);

      return value;
    }


    /**
    * @brief Get the number of elements in the queue.
    *
    * @return The number of elements.
    */
    size_t size() const noexcept
    {
      return m_size;
    }


  private:
    struct kv_pair_struct
    {
      K key;
      V value;
    };

    V const m_min;
    V const m_max;
    Array<kv_pair_struct> m_data;
    Array<size_t> m_index;
    size_t m_size;


    /**
    * @brief Fill a whole created in the heap.
    *
    * @param index The index of the hole to fill.
    */
    void fill(
        size_t const index)
    {
    }


    /**
    * @brief Correctly float an item up into the heap that was placed at the
    * bottom.
    *
    * @param index The index of the value to place.
    */
    void place(
        size_t const index)
    {
    }
};


}

#endif
