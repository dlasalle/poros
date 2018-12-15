/**
* @file VertexSet.hpp
* @brief The VertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-23
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/



#ifndef POROS_SRC_VERTEXSET_HPP
#define POROS_SRC_VERTEXSET_HPP


#include "Vertex.hpp"


namespace poros
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
