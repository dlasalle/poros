/**
* @file Aggregation.hpp
* @brief The Aggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-09
*/


#ifndef DOLOS_SRC_AGGREGATION_HPP
#define DOLOS_SRC_AGGREGATION_HPP


#include "Base.hpp"
#include "aggregation/VertexGrouping.hpp"
#include "graph/CSRGraphData.hpp"
#include "solidutils/Debug.hpp"
#include "solidutils/Array.hpp"


namespace dolos
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
        vtx_type numCoarseVertices,
        CSRGraphData data);

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
    CSRGraphData m_data;

};


}


#endif
