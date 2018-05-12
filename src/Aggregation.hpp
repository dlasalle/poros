/**
* @file Aggregation.hpp
* @brief The Aggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/


#ifndef DOLOS_SRC_AGGREGATION_HPP
#define DOLOS_SRC_AGGREGATION_HPP


#include "solidutils/Debug.hpp"
#include "Base.hpp"
#include "VertexGrouping.hpp"
#include <vector>


namespace dolos
{

class Aggregation
{
  public:
    /**
    * @brief Create a new aggregation from a vector. 
    *
    * @param coarseMap The cmap vector.
    * @param numCoarseVertices The number of coarse vertices.
    * @param data The graph data.
    */
    Aggregation(
        std::vector<vtx_type> && coarseMap,
        vtx_type numCoarseVertices,
        ICSRGraphData const * const data);

    /**
    * @brief Copy constructor.
    *
    * @param rhs The aggregation to copy.
    */
    Aggregation(
        Aggregation const & rhs);

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
        Aggregation const & rhs);

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
      ASSERT_LESS(v, m_coarseMap.size());
      ASSERT_LESS(m_coarseMap[v], m_numCoarseVertices);
      return m_coarseMap[v];
    }


    /**
    * @brief Get the set of vertices that have been grouped.
    *
    * @return The vertex groupings.
    */
    VertexGrouping coarseVertices() const noexcept;



  private:
    const vtx_type m_numCoarseVertices;
    std::vector<vtx_type> m_coarseMap;
    std::vector<vtx_type> m_finePrefix;
    std::vector<vtx_type> m_fineMap;
    ICSRGraphData const * const m_data;

};

}

#endif
