/**
* @file VertexGroup.hpp
* @brief The VertexGroup class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-12
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



#ifndef POROS_SRC_VERTEXGROUP_HPP
#define POROS_SRC_VERTEXGROUP_HPP

#include "graph/PermutedVertexSet.hpp"
#include "solidutils/Debug.hpp"

namespace poros
{

class VertexGroup
{
  public:
    class Iterator
    {
      public:
        Iterator(
            vtx_type const * ptr) :
          m_ptr(ptr)
        {
          // do nothing
        }

        inline Vertex operator*() const noexcept
        {
          return Vertex::make(*m_ptr);
        }

        inline Iterator const & operator++() noexcept
        {
          ++m_ptr;
          return *this;
        }

        inline Iterator const & operator+=(
            vtx_type const offset) noexcept
        {
          m_ptr += offset;
          return *this;
        }

        inline Iterator const & operator-=(
            vtx_type const offset) noexcept
        {
          m_ptr -= offset;
          return *this;
        }

        inline bool operator==(
            Iterator const & other) const noexcept
        {
          return m_ptr == other.m_ptr;
        }

        inline bool operator!=(
            Iterator const & other) const noexcept
        {
          return m_ptr != other.m_ptr;
        }

        private:
          vtx_type const * m_ptr;
    };

    /**
    * @brief Create a new vertex group.
    *
    * @param size The size of the group.
    * @param fineVertices The set of fine vertices in the group.
    * @param data The graph data.
    */
    VertexGroup(
        vtx_type const size,
        vtx_type const * const fineVertices) noexcept :
      m_size(size),
      m_fineVertices(fineVertices)
    {
      // do nothing
    }

    /**
    * @brief Get the iterator for the beginning of the vertex groups in this
    * grouping.
    *
    * @return The beginning iterator.
    */
    inline Iterator begin() const noexcept
    {
      return Iterator(m_fineVertices);
    }

    /**
    * @brief Get the iteartor for the end (one past the last) of the vertex
    * groups in this grouping.
    *
    * @return The ending iterator.
    */
    inline Iterator end() const noexcept
    {
      return Iterator(m_fineVertices+m_size);
    }

    inline Vertex operator[](vtx_type const index) const noexcept
    {
      ASSERT_LESS(index, m_size);
      return Vertex::make(m_fineVertices[index]);
    }

    /**
    * @brief Get the number of vertices in this group.
    *
    * @return The number of vertices.
    */
    inline vtx_type size() const noexcept
    {
      return m_size;
    }

  private:
    vtx_type const m_size;
    vtx_type const * const m_fineVertices;
 
};

}

#endif
