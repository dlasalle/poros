/**
* @file Alloc.hpp
* @brief Memory allocation utilities;
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/



#ifndef DOLOS_SRC_ALLOC_HPP
#define DOLOS_SRC_ALLOC_HPP



#include <cstring>
#include <new>
#include <string>


namespace dolos
{


class NotEnoughMemoryException :
    public std::bad_alloc
{
  public:
      NotEnoughMemoryException(
          size_t const numChunks,
          size_t const chunkSize) noexcept :
        std::bad_alloc(),
        m_msg(std::string("Failed to allocate ") + \
              std::to_string(numChunks*chunkSize) + \
              std::string(" bytes in ") + std::to_string(numChunks) + \
              std::string(" chunks of size ") + \
              std::to_string(chunkSize) + std::string("."))
      {
        // do nothing 
      }

      const char * what() const noexcept override
      {
        return m_msg.c_str();
      }

  private:
    std::string m_msg;
};


class Alloc
{
  public:
    /**
    * @brief Allocate a block of uninitialized memory that can be free'd with a
    * call to Alloc::free(). If the amount of memory
    * requested is 0, then nullptr will be returned.
    *
    * @tparam T The type of memory to allocate.
    * @param num The number of elements.
    *
    * @return The memory.
    *
    * @throws std::bad_alloc If the amount of memory fails to get allocated.
    */
    template<typename T>
    static T * uninitialized(
        size_t const num)
    {
      constexpr size_t const chunkSize = sizeof(T);

      size_t const numBytes = chunkSize*num;

      if (numBytes > 0) {
        T * const data = reinterpret_cast<T*>(malloc(numBytes));

        if (data == nullptr) {
          throw NotEnoughMemoryException(num, chunkSize);
        }
        return data;
      } else {
        return nullptr;
      }
    }

    /**
    * @brief Allocate and initialize a block of memory to a constant value.
    *
    * @tparam T The type of memory to allocate.
    * @param num The number of elements.
    * @param val The value to initialize elements to.
    *
    * @return The memory.
    *
    * @throws std::bad_alloc If the amount of memory fails to get allocated.
    */
    template<typename T>
    static T * initizialized(
        size_t const num,
        T const val = 0)
    {
      T * const data = uninitialized<T>(num);
      for (size_t i = 0; i < num; ++i) {
        data[i] = val;
      }

      return data;
    }

    /**
    * @brief Allocate and initialized memory a block of memory to a stepped
    * sequence: 
    *    {start, start+inc, start+(inc*2), ... start+(inc*(num-1))}
    *
    * @tparam T The type of memory to allocate.
    * @param num The number of elements.
    * @param start The starting value.
    * @param inc The increment between successive elements.
    *
    * @return The memory.
    *
    * @throws std::bad_alloc If the amount of memory fails to get allocated.
    */
    template<typename T>
    static T * initStepped(
        size_t const num,
        T const start = 0,
        T const inc = 1)
    {
      T * const data = uninitialized<T>(num);
      T val = start;
      for (size_t i = 0; i < num; ++i) {
        data[i] = val;
        val += inc;
      }

      return data;
    }

    /**
    * @brief Allocate and and fill a block of memory from another block.
    *
    * @tparam T The type of memory to allocate.
    * @param ptr The other bock of memory.
    * @param num The size of the other block (in terms of elements).
    *
    * @return The memory.
    *
    * @throws std::bad_alloc If the amount of memory fails to get allocated.
    */
    template<typename T>
    static T * duplicate(
        T const * const ptr,
        size_t const num)
    {
      T * const data = uninitialized<T>(num);
      for (size_t i = 0; i < num; ++i) {
        data[i] = ptr[i];
      }

      return data;
    }




    /**
    * @brief Free a block of memory allocated with this class.
    *
    * @tparam T The type of memory to free.
    * @param ptr A pointer to the memory to free.
    */
    template<typename T>
    static void free(
        T * const ptr)
    {
      if (ptr != nullptr) {
        std::free(ptr);
      }
    }
};

}


#endif
