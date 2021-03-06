/**
* @file Aggregation.hpp
* @brief The Aggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-09
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


#ifndef POROS_SRC_AGGREGATION_HPP
#define POROS_SRC_AGGREGATION_HPP


#include "Base.hpp"
#include "aggregation/VertexGrouping.hpp"
#include "solidutils/Debug.hpp"
#include "solidutils/Array.hpp"


namespace poros
{

class Aggregation
{
  public:
    /**
    * @brief Create a new aggregation from a coarse map 
    *
    * @param coarseMap The cmap vector.
    * @param numCoarseVertices The number of coarse vertices.
    * @param data The graph data.
    */
    Aggregation(
        sl::Array<vtx_type> coarseMap,
        vtx_type numCoarseVertices);

    /**
    * @brief Copy constructor.
    *
    * @param rhs The aggregation to copy.
    */
    Aggregation(
        Aggregation const & rhs) = delete;

    /**
    * @brief The move constructor.
    *
    * @param rhs The aggregation to move.
    */
    Aggregation(
        Aggregation && rhs);

    /**
    * @brief The copy assignment operator.
    *
    * @param rhs The aggregation to copy.
    *
    * @return This aggregation.
    */
    Aggregation& operator=(
        Aggregation const & rhs) = delete;

    /**
    * @brief The move assignment operator.
    *
    * @param rhs The aggregation to move.
    *
    * @return This aggregation.
    */
    Aggregation& operator=(
        Aggregation && rhs);


    /**
    * @brief Get the number of coarse vertices in this aggregation.
    *
    * @return The number of coarse vertices.
    */
    vtx_type getNumCoarseVertices() const noexcept
    {
      return m_numCoarseVertices;
    }


    /**
    * @brief Get the mapping of a vertex.
    *
    * @param v The vertex.
    *
    * @return The coarse vertex number.
    */
    vtx_type getCoarseVertexNumber(
        const vtx_type v) const noexcept
    {
      ASSERT_LESS(v, m_numFineVertices);
      ASSERT_LESS(m_coarseMap[v], m_numCoarseVertices);
      return m_coarseMap[v];
    }


    /**
    * @brief Get the set of vertices that have been grouped.
    *
    * @return The vertex groupings.
    */
    VertexGrouping coarseVertices() const noexcept;


    /**
    * @brief Fill the memory location with the coarse map.
    *
    * @param data The memory location.
    */
    void fillCoarseMap(
        vtx_type * data) const noexcept;

    vtx_type const * finePrefix() const noexcept
    {
      return m_finePrefix.data();
    }

    vtx_type const * fineMap() const noexcept
    {
      return m_fineMap.data();
    }

    vtx_type const * cmap() const noexcept
    {
      return m_coarseMap.data();
    }

  private:
    vtx_type m_numFineVertices;
    vtx_type m_numCoarseVertices;
    sl::Array<vtx_type> m_coarseMap;
    sl::Array<vtx_type> m_finePrefix;
    sl::Array<vtx_type> m_fineMap;

};


}


#endif
