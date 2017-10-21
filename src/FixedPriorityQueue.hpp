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

    FixedPriorityQueue(
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
      ASSERT_LESS(static_cast<size_t>(value), m_index.size());
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
      ASSERT_LESS(static_cast<size_t>(value), m_index.size());
      ASSERT_EQUAL(m_index[value], NULL_INDEX);

      size_t const index = m_size++;
      m_index[value] = index;
      m_data[index].key = key;
      m_data[index].value = value;

      place(index);
    }


    /**
    * @brief Update the key associated with a given value.
    *
    * @param key The new key for the value.
    * @param value The value.
    */
    void update(
        K const key,
        V const value) noexcept
    {
      ASSERT_LESS(static_cast<size_t>(value), m_index.size());
      ASSERT_NOTEQUAL(m_index[value], NULL_INDEX);

      size_t const index = m_index[value]; 
      m_data[index].key = key;

      // update position
    }


    /**
    * @brief Get the key associated with the given value.
    *
    * @param value The value.
    *
    * @return The key.
    */
    K get(
        V const value) noexcept
    {
      ASSERT_LESS(static_cast<size_t>(value), m_index.size());
      ASSERT_NOTEQUAL(m_index[value], NULL_INDEX);

      return m_data[m_index[value]].data;
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
    * @brief Get the index of the parent.
    *
    * @param index
    *
    * @return 
    */
    size_t parentIndex(
        size_t const index) const noexcept
    {
      return index / 2;
    }


    /**
    * @brief Get the index of the left child node.
    *
    * @param index The current index.
    *
    * @return The left child index.
    */
    size_t leftChildIndex(
        size_t const index) const noexcept
    {
      return (index * 2)+1;
    }


    /**
    * @brief Get the index of the right child node.
    *
    * @param index The current index.
    *
    * @return The right child index.
    */
    size_t rightChildIndex(
        size_t const index) const noexcept
    {
      return leftChildIndex(index) + 1;
    }



    /**
    * @brief Fill a whole created in the heap.
    *
    * @param index The index of the hole to fill.
    */
    void fill(
        size_t const index) noexcept
    {
      // what we'll do is move the bottom node to this position
      m_data[index] = m_data[--m_size];
      m_index[m_data[index]] = index;

      siftDown(index); 
    }


    /**
    * @brief Correctly float an item up into the heap.
    *
    * @param index The index of the value to place.
    */
    void siftUp(
        size_t index) noexcept
    {
      while (index > 0) {
        size_t const parent = parentIndex(index);
        if (m_data[parent].key >= m_data[index].key) {
          // reached a valid state
          break;
        }
        V const currentValue = m_data[index].value;
        V const parentValue = m_data[parent].value; 
        std::swap(m_index[currentValue], m_index[parentValue]);
        std::swap(m_data[index], m_data[parentIndex]);
        index = parent;
      }
    }

    /**
    * @brief Correctly sink an item up into the heap.
    *
    * @param index The index of the value to place.
    */
    void siftDown(
        size_t const index) noexcept
    {
      while (index < m_size) {
        size_t const leftIndex = left
        
      }
    }

};


}

#endif
