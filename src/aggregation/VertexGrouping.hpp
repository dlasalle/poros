/**
* @file VertexGrouping.hpp
* @brief The VertexGrouping class.
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


#ifndef POROS_SRC_VERTEXGROUPING_HPP
#define POROS_SRC_VERTEXGROUPING_HPP

#include "aggregation/VertexGroup.hpp"

namespace poros
{

class VertexGrouping
{
  public:
  class Iterator
  {
    public:
      Iterator(
          vtx_type const index,
          vtx_type const * const finePrefix,
          vtx_type const * const fineMap) :
        m_index(index),
        m_finePrefix(finePrefix),
        m_fineMap(fineMap)
      {
        // do nothing 
      }

      inline VertexGroup operator*() const noexcept
      {
        return VertexGroup(
            m_finePrefix[m_index+1]-m_finePrefix[m_index],
            m_fineMap + m_finePrefix[m_index]);
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
        vtx_type const * const m_finePrefix;
        vtx_type const * const m_fineMap;
  };

  /**
  * @brief Create a new vertex grouping.
  *
  * @param numCoarseVertices The number of coarse vertices in this grouping.
  * @param finePrefix The prefixsum of the fine vertices per coarse vertex.
  * @param fineMap The set of fine vertices in each coarse vertex.
  */
  VertexGrouping(
      vtx_type const numCoarseVertices,
      vtx_type const * const finePrefix,
      vtx_type const * const fineMap) noexcept :
    m_numCoarseVertices(numCoarseVertices),
    m_finePrefix(finePrefix),
    m_fineMap(fineMap)
  {
    // do nothing
  }

  /**
  * @brief Get the iterator for the beginning of the vertex groups in this
  * grouping.
  *
  * @return The beginning iterator.
  */
  inline Iterator begin() const
  {
    return Iterator(0, m_finePrefix, m_fineMap); 
  }

  /**
  * @brief Get the iteartor for the end (one past the last) of the vertex
  * groups in this grouping.
  *
  * @return The ending iterator.
  */
  inline Iterator end() const
  {
    return Iterator(m_numCoarseVertices, m_finePrefix, m_fineMap);
  }

  private:
    vtx_type const m_numCoarseVertices; 
    vtx_type const * const m_finePrefix;
    vtx_type const * const m_fineMap;

};

}

#endif

