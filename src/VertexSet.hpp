/**
* @file VertexSet.hpp
* @brief The VertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-23
*/



#ifndef DOLOS_SRC_VERTEXSET_HPP
#define DOLOS_SRC_VERTEXSET_HPP


#include "Vertex.hpp"


namespace dolos
{


class VertexSet
{
  public:
    class Iterator
    {
      public:
        Iterator(
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

        inline Vertex operator*() const
        {
          return Vertex(m_index, m_vertexWeight, m_edgePrefix, m_edgeList, \
              m_edgeWeight);
        }

        inline Iterator const & operator++()
        {
          ++m_index;
          return *this;
        }

        inline bool operator==(
            Iterator const & other) const
        {
          return m_index == other.m_index;
        }

        inline bool operator!=(
            Iterator const & other) const
        {
          return m_index != other.m_index;
        }

      private:
        adj_type m_index;
        wgt_type const * const m_vertexWeight;
        adj_type const * const m_edgePrefix;
        vtx_type const * const m_edgeList;
        wgt_type const * const m_edgeWeight;
    };

    /**
    * @brief Create a new vertex set.
    *
    * @param begin The starting vertex.
    * @param end The ending vertex (exclusive).
    * @param weight The vector of vertex weights.
    * @param edgePrefix THe edge prefix vector.
    * @param edgeList The edge list vector.
    * @param edgeWeight The edge weight vector.
    */
    VertexSet(
        vtx_type const begin,
        vtx_type const end,
        wgt_type const * const weight,
        adj_type const * const edgePrefix,
        vtx_type const * const edgeList,
        wgt_type const * const edgeWeight) noexcept :
      m_begin(begin),
      m_end(end),
      m_weight(weight),
      m_edgePrefix(edgePrefix),
      m_edgeList(edgeList),
      m_edgeWeight(edgeWeight)
    {
      // do nothing
    }

    /**
    * @brief Get the begin iterator to this vertex set.
    *
    * @return The iterator.
    */
    inline Iterator begin() const noexcept
    {
      return Iterator(m_begin, m_weight, m_edgePrefix, m_edgeList, \
          m_edgeWeight);
    }

    /**
    * @brief Get an end iterator for the vertex set.
    *
    * @return The end iterator.
    */
    inline Iterator end() const noexcept
    {
      return Iterator(m_end, m_weight, m_edgePrefix, m_edgeList, \
          m_edgeWeight);
    }

    /**
    * @brief Get the number of vertices in this vertex set.
    *
    * @return The number of vertices.
    */
    inline vtx_type size() const noexcept
    {
      return m_end - m_begin;
    }
  
  private:
    vtx_type const m_begin;
    vtx_type const m_end;
    wgt_type const * const m_weight;
    adj_type const * const m_edgePrefix;
    vtx_type const * const m_edgeList;
    wgt_type const * const m_edgeWeight;
};


}


#endif
