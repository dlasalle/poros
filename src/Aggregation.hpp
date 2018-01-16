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
    */
    Aggregation(
        std::vector<vtx_type> && coarseMap,
        vtx_type numCoarseVertices);


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
    vtx_type getCoarseVertex(
        const vtx_type v) const noexcept
    {
      ASSERT_LESS(v, m_coarseMap.size());
      ASSERT_LESS(m_coarseMap[v], m_numCoarseVertices);
      return m_coarseMap[v];
    }


  private:
    const vtx_type m_numCoarseVertices;
    std::vector<vtx_type> m_coarseMap;
};

}

#endif
