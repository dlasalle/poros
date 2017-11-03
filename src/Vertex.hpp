/**
* @file Vertex.hpp
* @brief The Vertex class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-23
*/


#ifndef DOLOS_SRC_VERTEX_HPP
#define DOLOS_SRC_VERTEX_HPP


#include "Base.hpp"
#include "EdgeSet.hpp"


namespace dolos
{


class Vertex
{
  public:
    /**
    * @brief Create a new vertex.
    *
    * @param index The vertex's index (ID). This is used index into the
    * following vectors.
    * @param vertexWeight The vector of vertex weights.
    * @param edgePrefix The vector of edge prefixes.
    * @param edgeList The vector of edge endpoints.
    * @param edgeWeight The vector of edge weights.
    */
    Vertex(
        vtx_type const index,
        wgt_type const * const vertexWeight,
        adj_type const * const edgePrefix,
        vtx_type const * const edgeList,
        wgt_type const * const edgeWeight) noexcept :
      m_index(index),
      m_vertexWeight(vertexWeight),
      m_edgePrefix(edgePrefix),
      m_edgeList(edgeList),
      m_edgeWeight(edgeWeight)
    {
      // do nothing 
    }


    /**
    * @brief Get the index of this vertex (it's id).
    *
    * @return The index.
    */
    inline vtx_type getIndex() const noexcept
    {
      return m_index;
    }


    /**
    * @brief Get the weight of this vertex.
    *
    * @return The weight of this vertex.
    */
    inline wgt_type getWeight() const noexcept
    {
      return m_vertexWeight[m_index];
    }


    /**
    * @brief Get the edges of this vertex.
    *
    * @return The edges of this vertex.
    */
    inline EdgeSet getEdges() const noexcept
    {
      return EdgeSet(m_edgePrefix[m_index], m_edgePrefix[m_index+1], \
          m_edgeList, m_edgeWeight);
    }


    /**
    * @brief Get the number of edges incident to this vertex.
    *
    * @return The number of edges incident to this vertex.
    */
    inline adj_type getNumEdges() const noexcept
    {
      return m_edgePrefix[m_index+1] - m_edgePrefix[m_index];
    }


  private:
    vtx_type const m_index;
    wgt_type const * const m_vertexWeight;
    adj_type const * const m_edgePrefix;
    vtx_type const * const m_edgeList;
    wgt_type const * const m_edgeWeight;
};


}


#endif
