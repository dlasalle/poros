/**
* @file PermutedVertexSet.hpp
* @brief The PermutedVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2018-01-14
*/



#ifndef DOLOS_SRC_PERMUTEDVERTEXSET_HPP
#define DOLOS_SRC_PERMUTEDVERTEXSET_HPP


#include "solidutils/Random.hpp"
#include "Vertex.hpp"
#include "Base.hpp"
#include <vector>


namespace dolos
{


class PermutedVertexSet
{
  public:
    class Iterator
    {
      public:
        Iterator(
            vtx_type const index,
            vtx_type const * const set,
            ICSRGraphData const * const data) noexcept :
          m_index(index),
          m_set(set),
          m_vertexWeight(data->vertexWeight()),
          m_edgePrefix(data->edgePrefix()),
          m_edgeList(data->edgeList()),
          m_edgeWeight(data->edgeWeight())
        {
          // do nothing
        }

        inline Vertex operator*() const
        {
          return Vertex(m_set[m_index], m_vertexWeight, m_edgePrefix, \
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
        vtx_type const * const m_set;

        // we explicitly store the pointers, rather than use the
        // ICSRGraphData structure so as to reduce access time as
        // the iterator is dereferenced
        wgt_type const * const m_vertexWeight;
        adj_type const * const m_edgePrefix;
        vtx_type const * const m_edgeList;
        wgt_type const * const m_edgeWeight;
    };

    /**
    * @brief Create a new vertex set with a permuted order.
    *
    * @param size The number of vertices.
    * @param vertices The set of vertices (order matters).
    * @param data The data of the graph.
    */
    PermutedVertexSet(
        vtx_type const size,
        vtx_type const * const vertices,
        ICSRGraphData const * const data) noexcept :
      m_set(vertices, vertices+size),
      m_data(data)
    {
      // do nothing
    }


    /**
    * @brief Move constructor.
    *
    * @param other The set to move.
    */
    PermutedVertexSet(
        PermutedVertexSet && other) :
      m_set(std::move(other.m_set)),
      m_data(other.m_data)
    {
      // do nothing
    }

    /**
    * @brief Virtual destructor.
    */
    virtual ~PermutedVertexSet()
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
      return Iterator(0, m_set.data(), m_data);
    }

    /**
    * @brief Get an end iterator for the vertex set.
    *
    * @return The end iterator.
    */
    inline Iterator end() const noexcept
    {
      return Iterator(m_set.size(), m_set.data(), m_data);
    }

    /**
    * @brief Get the number of vertices in this vertex set.
    *
    * @return The number of vertices.
    */
    inline vtx_type size() const noexcept
    {
      return m_set.size();
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
      return Vertex(m_set[index], m_data->vertexWeight(), \
          m_data->edgePrefix(), m_data->edgeList(), m_data->edgeWeight());
    }

  
  private:
    std::vector<vtx_type> m_set;
    ICSRGraphData const * const m_data;

    // disable copying
    PermutedVertexSet(
        PermutedVertexSet const & other) = delete;
    PermutedVertexSet& operator=(
        PermutedVertexSet const & other) = delete;

};


}




#endif
