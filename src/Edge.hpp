/**
* @file Edge.hpp
* @brief The Edge class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-23
*/



#ifndef DOLOS_SRC_EDGE_HPP
#define DOLOS_SRC_EDGE_HPP


#include "Base.hpp"


namespace dolos
{


class Edge
{
  public:
    /**
    * @brief Create a new edge with a pointer to the given vertex and a pointer
    * to the given weight.
    *
    * @param endpoint
    * @param weight
    */
    Edge(
        adj_type const index,
        vtx_type const * const edgeList,
        wgt_type const * const edgeWeight) noexcept :
      m_index(index),
      m_edgeList(edgeList),
      m_edgeWeight(edgeWeight)
    {
      // do nothing
    }


    /**
    * @brief Get the index of the edge.
    *
    * @return The index of the edge.
    */
    inline adj_type index() const noexcept
    {
      return m_index;
    }
    

    /**
    * @brief Get the weight of this edge.
    *
    * @return 
    */
    inline wgt_type weight() const noexcept
    {
      return m_edgeWeight[m_index];
    }


    /**
    * @brief Get the vertex at the other end of this edge.
    *
    * @return The vertex.
    */
    inline vtx_type getVertex() const noexcept
    {
      return m_edgeList[m_index];
    }

  private:
    adj_type const m_index;
    vtx_type const * const m_edgeList;
    wgt_type const * const m_edgeWeight;
};


}

#endif
