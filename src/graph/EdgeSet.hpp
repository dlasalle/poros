/**
* @file EdgeSet.hpp
* @brief The EdgeSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-23
*/


#ifndef DOLOS_SRC_EDGESET_HPP
#define DOLOS_SRC_EDGESET_HPP


#include "Edge.hpp"


namespace dolos
{


class EdgeSet
{
  public:
    class Iterator
    {
      public:
        Iterator(
            adj_type const index,
            vtx_type const * const edgeList,
            wgt_type const * const edgeWeight) noexcept :
          m_index(index),
          m_edgeList(edgeList),
          m_edgeWeight(edgeWeight)
        {
          // do nothing
        }

        inline Edge operator*() const
        {
          return Edge(m_index, m_edgeList, m_edgeWeight);
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
        vtx_type const * const m_edgeList;
        wgt_type const * const m_edgeWeight;
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
        adj_type const end,
        vtx_type const * const edgeList,
        wgt_type const * const edgeWeight) :
      m_begin(begin),
      m_end(end),
      m_edgeList(edgeList),
      m_edgeWeight(edgeWeight)
    {
      // do nothing
    }

    /**
    * @brief Get an iterator to the beginning of this edgeset.
    *
    * @return The iterator.
    */
    inline Iterator begin() const noexcept
    {
      return Iterator(m_begin, m_edgeList, m_edgeWeight);
    }

    /**
    * @brief Get an iterator to the end of this edgeset (one past the last
    * edge).
    *
    * @return The iterator.
    */
    inline Iterator end() const noexcept
    {
      return Iterator(m_end, m_edgeList, m_edgeWeight);
    }

    /**
    * @brief Get the number of edges in this edgeset.
    *
    * @return The number of edges in this edge set.
    */
    inline adj_type size() const noexcept
    {
      return m_end - m_begin;
    }
  
  private:
    adj_type const m_begin;
    adj_type const m_end;
    vtx_type const * const m_edgeList;
    wgt_type const * const m_edgeWeight;
};


}


#endif
