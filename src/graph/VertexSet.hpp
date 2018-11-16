/**
* @file VertexSet.hpp
* @brief The VertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-23
*/



#ifndef DOLOS_SRC_VERTEXSET_HPP
#define DOLOS_SRC_VERTEXSET_HPP


#include "Vertex.hpp"


namespace dolos
{


class VertexSet
{
  public:
    class Iterator
    {
      public:
        static Iterator make(
            vtx_type const index) noexcept
        {
          Iterator i;
          i.m_index = index;

          return i;
        }

        inline Vertex operator*() const noexcept
        {
          return Vertex::make(m_index);
        }

        inline Iterator const & operator++() noexcept
        {
          ++m_index;
          return *this;
        }

        inline Iterator const & operator+=(
            vtx_type const offset) noexcept
        {
          m_index += offset;
          return *this;
        }

        inline Iterator const & operator-=(
            vtx_type const offset) noexcept
        {
          m_index -= offset;
          return *this;
        }

        inline bool operator==(
            Iterator const & other) const noexcept
        {
          return m_index == other.m_index;
        }

        inline bool operator!=(
            Iterator const & other) const noexcept
        {
          return m_index != other.m_index;
        }

      private:
        vtx_type m_index;
    };

    /**
    * @brief Create a new vertex set.
    *
    * @param begin The starting vertex.
    * @param end The ending vertex (exclusive).
    */
    VertexSet(
        vtx_type const begin,
        vtx_type const end) noexcept :
      m_begin(begin),
      m_end(end)
    {
      // do nothing
    }

    /**
    * @brief Get the begin iterator to this vertex set.
    *
    * @return The iterator.
    */
    inline Iterator begin() const noexcept
    {
      return Iterator::make(m_begin);
    }

    /**
    * @brief Get an end iterator for the vertex set.
    *
    * @return The end iterator.
    */
    inline Iterator end() const noexcept
    {
      return Iterator::make(m_end);
    }

    /**
    * @brief Get the number of vertices in this vertex set.
    *
    * @return The number of vertices.
    */
    inline vtx_type size() const noexcept
    {
      return m_end - m_begin;
    }


    /**
    * @brief Get a vertex at a given index.
    *
    * @param index The index.
    *
    * @return The vertex.
    */
    inline Vertex operator[](
        vtx_type const index) const noexcept
    {
      return Vertex::make(index);
    }

  private:
    vtx_type m_begin;
    vtx_type m_end;
};


}


#endif
