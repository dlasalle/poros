/**
* @file RandomOrderVertexSet.hpp
* @brief The RandomOrderVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2018-01-14
*/



#ifndef DOLOS_SRC_RANDOMORDERVERTEXSET_HPP
#define DOLOS_SRC_RANDOMORDERVERTEXSET_HPP


#include "solidutils/Random.hpp"
#include "Vertex.hpp"
#include "Base.hpp"
#include <vector>


namespace dolos
{


class RandomOrderVertexSet
{
  public:
    class Iterator
    {
      public:
        Iterator(
            vtx_type const index,
            vtx_type const * const perm,
            wgt_type const * const vertexWeight,
            adj_type const * const edgePrefix,
            vtx_type const * const edgeList,
            wgt_type const * const edgeWeight) noexcept :
          m_index(index),
          m_perm(perm),
          m_vertexWeight(vertexWeight),
          m_edgePrefix(edgePrefix),
          m_edgeList(edgeList),
          m_edgeWeight(edgeWeight)
        {
          // do nothing
        }

        inline Vertex operator*() const
        {
          return Vertex(m_perm[m_index], m_vertexWeight, m_edgePrefix, \
              m_edgeList, m_edgeWeight);
        }

        inline Iterator const & operator++()
        {
          ++m_index;
          return *this;
        }

        inline Iterator const & operator+=(
            vtx_type const offset)
        {
          m_index += offset;
          return *this;
        }

        inline Iterator const & operator-=(
            vtx_type const offset)
        {
          m_index -= offset;
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
        vtx_type const * const m_perm;
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
    RandomOrderVertexSet(
        vtx_type const begin,
        vtx_type const end,
        wgt_type const * const weight,
        adj_type const * const edgePrefix,
        vtx_type const * const edgeList,
        wgt_type const * const edgeWeight) noexcept :
      m_begin(begin),
      m_end(end),
      m_perm(end - begin),
      m_weight(weight),
      m_edgePrefix(edgePrefix),
      m_edgeList(edgeList),
      m_edgeWeight(edgeWeight)
    {
      sl::Random::fillWithPerm(&m_perm, begin);
    }


    /**
    * @brief Move constructor.
    *
    * @param other The set to move.
    */
    RandomOrderVertexSet(
        RandomOrderVertexSet && other) :
      m_begin(other.m_begin),
      m_end(other.m_end),
      m_perm(std::move(other.m_perm)),
      m_weight(other.m_weight),
      m_edgePrefix(other.m_edgePrefix),
      m_edgeList(other.m_edgeList),
      m_edgeWeight(other.m_edgeWeight)
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
      return Iterator(m_begin, m_perm.data(), m_weight, m_edgePrefix, \
          m_edgeList, m_edgeWeight);
    }

    /**
    * @brief Get an end iterator for the vertex set.
    *
    * @return The end iterator.
    */
    inline Iterator end() const noexcept
    {
      return Iterator(m_end, m_perm.data(), m_weight, m_edgePrefix, \
          m_edgeList, m_edgeWeight);
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


    /**
    * @brief Get a vertex at a given index.
    *
    * @param index The index.
    *
    * @return The vertex.
    */
    inline Vertex operator[](
        size_t const index) const
    {
      return Vertex(m_perm[index], m_weight, m_edgePrefix, m_edgeList, \
          m_edgeWeight);
    }

  
  private:
    vtx_type const m_begin;
    vtx_type const m_end;
    std::vector<vtx_type> m_perm;
    wgt_type const * const m_weight;
    adj_type const * const m_edgePrefix;
    vtx_type const * const m_edgeList;
    wgt_type const * const m_edgeWeight;

    // disable copying
    RandomOrderVertexSet(
        RandomOrderVertexSet const & other) = delete;
    RandomOrderVertexSet& operator=(
        RandomOrderVertexSet const & other) = delete;

};


}




#endif
