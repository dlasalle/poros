/**
* @file EdgeSet.hpp
* @brief The EdgeSet class.
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


#ifndef POROS_SRC_EDGESET_HPP
#define POROS_SRC_EDGESET_HPP


#include "Edge.hpp"


namespace poros
{


class EdgeSet
{
  public:
    class Iterator
    {
      public:
        Iterator(
            adj_type const index) noexcept :
          m_index(index)
        {
          // do nothing
        }

        Edge operator*() const
        {
          return Edge::make(m_index);
        }

        Iterator const & operator++()
        {
          ++m_index;
          return *this;
        }

        bool operator==(
            Iterator const & other) const
        {
          return m_index == other.m_index;
        }

        bool operator!=(
            Iterator const & other) const
        {
          return m_index != other.m_index;
        }

      private:
        adj_type m_index;
    };

    /**
    * @brief Create a new edgeset.
    *
    * @param begin The starting index of the edge set.
    * @param end The ending index of the edge set.
    * @param edgeList The edge list array.
    * @param edgeWeight The edge weight array.
    */
    EdgeSet(
        adj_type const begin,
        adj_type const end) :
      m_begin(begin),
      m_end(end)
    {
      // do nothing
    }

    /**
    * @brief Get an iterator to the beginning of this edgeset.
    *
    * @return The iterator.
    */
    Iterator begin() const noexcept
    {
      return Iterator(m_begin);
    }

    /**
    * @brief Get an iterator to the end of this edgeset (one past the last
    * edge).
    *
    * @return The iterator.
    */
    Iterator end() const noexcept
    {
      return Iterator(m_end);
    }

    /**
    * @brief Get the number of edges in this edgeset.
    *
    * @return The number of edges in this edge set.
    */
    adj_type size() const noexcept
    {
      return m_end - m_begin;
    }
  
  private:
    adj_type m_begin;
    adj_type m_end;
};


}


#endif
