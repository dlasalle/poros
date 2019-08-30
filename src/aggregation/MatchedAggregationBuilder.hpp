/**
* @file MatchedAggregationBuilder.hpp
* @brief The MatchedAggregationBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2018-01-14
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




#ifndef POROS_SRC_MATCHEDAGGREGATIONBUILDER_HPP
#define POROS_SRC_MATCHEDAGGREGATIONBUILDER_HPP


#include "aggregation/Aggregation.hpp"
#include "solidutils/Debug.hpp"
#include "Base.hpp"


namespace poros
{

class MatchedAggregationBuilder
{
  public:
    /**
    * @brief Create a new aggregation builder.
    *
    * @param numVertices The number of vertices that will be matched.
    */
    MatchedAggregationBuilder(
        vtx_type numVertices);


    /**
    * @brief Build an aggregation from this matching.
    *
    * @return The aggregation. 
    */
    Aggregation build() const;


    /**
    * @brief Check if a vertex is matched.
    *
    * @param vertex The vertex.
    *
    * @return True if the vertex has been matched.
    */
    inline bool isMatched(
        vtx_type const vertex) const noexcept
    {
      ASSERT_LESS(static_cast<size_t>(vertex), m_match.size());

      return m_match[vertex] != NULL_VTX;
    }


    /**
    * @brief Match two unmatched vertices.
    *
    * @param first The first vertex to match.
    * @param second The second vertex to match.
    */
    inline void match(
        vtx_type const first,
        vtx_type const second) noexcept
    {
      ASSERT_LESS(static_cast<size_t>(first), m_match.size());
      ASSERT_LESS(static_cast<size_t>(second), m_match.size());
      ASSERT_EQUAL(m_match[first], NULL_VTX);
      ASSERT_EQUAL(m_match[second], NULL_VTX);

      m_match[first] = second;
      m_match[second] = first;
    }

    /**
    * @brief Get the next unmatched vertex. This function amortizes the cont
    * of a linear search over subsequent calls.
    *
    * @return The unmatched vertex.
    */
    inline vtx_type getNextUnmatched() noexcept
    {
      while (static_cast<size_t>(m_nextUnmatched) < m_match.size() && \
          isMatched(m_nextUnmatched)) {
        ++m_nextUnmatched;
      }

      return m_nextUnmatched;
    }

  private:
    vtx_type m_nextUnmatched;
    std::vector<vtx_type> m_match;
};

}


#endif
