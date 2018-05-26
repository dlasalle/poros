/**
* @file MatchedAggregationBuilder.hpp
* @brief The MatchedAggregationBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2018-01-14
*/




#ifndef DOLOS_SRC_MATCHEDAGGREGATIONBUILDER_HPP
#define DOLOS_SRC_MATCHEDAGGREGATIONBUILDER_HPP


#include "aggregation/Aggregation.hpp"
#include "graph/CSRGraphData.hpp"
#include "solidutils/Debug.hpp"
#include "Base.hpp"


namespace dolos
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
    * @param data The graph data.
    *
    * @return The aggregation. 
    */
    Aggregation build(
        CSRGraphData data) const;


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
      ASSERT_LESS(vertex, m_match.size());

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
      ASSERT_LESS(first, m_match.size());
      ASSERT_LESS(second, m_match.size());
      ASSERT_EQUAL(m_match[first], NULL_VTX);
      ASSERT_EQUAL(m_match[second], NULL_VTX);

      m_match[first] = second;
      m_match[second] = first;
    }

    /**
    * @brief Get the next unmatched vertex. This function amortizes the const
    * of a linear search over subsequent calls.
    *
    * @return The unmatched vertex.
    */
    inline vtx_type getNextUnmatched() noexcept
    {
      while (m_nextUnmatched < m_match.size() && isMatched(m_nextUnmatched)) {
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
