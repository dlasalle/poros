/**
* @file PermutedVertexSet.hpp
* @brief The PermutedVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2018-01-14
*/



#ifndef POROS_SRC_PERMUTEDVERTEXSET_HPP
#define POROS_SRC_PERMUTEDVERTEXSET_HPP


#include "Vertex.hpp"
#include "Base.hpp"

#include <vector>
#include <memory>


namespace poros
{


class PermutedVertexSet
{
  public:
    class Iterator
    {
      public:
        static Iterator make(
            vtx_type const * const ptr) noexcept
        {
          Iterator i;
          i.m_ptr = ptr;

          return i;
        }

        inline Vertex operator*() const
        {
          return Vertex::make(*m_ptr);
        }

        inline Iterator const & operator++()
        {
          ++m_ptr;
          return *this;
        }

        inline Iterator const & operator+=(
            vtx_type const offset)
        {
          m_ptr += offset;
          return *this;
        }

        inline Iterator const & operator-=(
            vtx_type const offset)
        {
          m_ptr -= offset;
          return *this;
        }

        inline bool operator==(
            Iterator const & other) const
        {
          return m_ptr == other.m_ptr;
        }

        inline bool operator!=(
            Iterator const & other) const
        {
          return m_ptr != other.m_ptr;
        }

      private:
        vtx_type const * m_ptr;
    };

    /**
    * @brief Create a new vertex set with a permuted order.
    *
    * @param vertices The set of vertices (order matters).
    * @param size The number of vertices.
    */
    PermutedVertexSet(
        std::unique_ptr<vtx_type[]> set,
        vtx_type const size) noexcept :
      m_size(size),
      m_set(std::move(set))
    {
      // do nothing
    }

    /**
    * @brief Create a new vertex set with a permuted order.
    *
    * @param vertices The set of vertices (order matters).
    * @param size The number of vertices.
    */
    PermutedVertexSet(
        vtx_type const * const set,
        vtx_type const size) noexcept :
      m_size(size),
      m_set(new vtx_type[m_size])
    {
      std::copy(set, set+size, m_set.get());
    }

    /**
    * @brief Move constructor.
    *
    * @param other The set to move.
    */
    PermutedVertexSet(
        PermutedVertexSet && other) noexcept :
      m_size(other.m_size),
      m_set(std::move(other.m_set))
    {
      other.m_size = 0;
      other.m_set.reset(nullptr);
    }

    /**
    * @brief Deleted copy constructor.
    *
    * @param other The object to copy..
    */
    PermutedVertexSet(
        PermutedVertexSet const & other) = delete;

    /**
    * @brief Deleted copy assignment operator.
    *
    * @param other The object to copy..
    *
    * @return This.
    */
    PermutedVertexSet& operator=(
        PermutedVertexSet const & other) = delete;

    /**
    * @brief Get the begin iterator to this vertex set.
    *
    * @return The iterator.
    */
    inline Iterator begin() const noexcept
    {
      return Iterator::make(m_set.get());
    }

    /**
    * @brief Get an end iterator for the vertex set.
    *
    * @return The end iterator.
    */
    inline Iterator end() const noexcept
    {
      return Iterator::make(m_set.get() + m_size);
    }

    /**
    * @brief Get the number of vertices in this vertex set.
    *
    * @return The number of vertices.
    */
    inline vtx_type size() const noexcept
    {
      return m_size;
    }

    /**
    * @brief Get a vertex at a given index.
    *
    * @param index The index.
    *
    * @return The vertex.
    */
    inline Vertex operator[](
        size_t const index) const noexcept
    {
      return Vertex::make(m_set[index]);
    }

  
  private:
    vtx_type m_size;
    std::unique_ptr<vtx_type[]> m_set;
};


static_assert(std::is_pod<PermutedVertexSet::Iterator>::value, \
    "Vertex must be trivial.");

}




#endif
