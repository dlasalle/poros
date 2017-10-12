/**
* @file ConstantGraph.hpp
* @brief The ConstantGraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-06
*/



#ifndef DOLOS_SRC_CONSTANTGRAPH_HPP
#define DOLOS_SRC_CONSTANTGRAPH_HPP


#include <cstdlib>
#include "Debug.hpp"
#include "Base.hpp"
#include "IAllocatedData.hpp"


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
      m_endpoint(edgeList),
      m_weight(edgeWeight)
    {
      // do nothing
    }
    

    inline vtx_type getEndpoint() const noexcept
    {
      return m_edgeList[index];
    }


    inline wgt_type getWeight() const noexcept
    {
      return m_edgeWeight[index];
    }


  private:
    vtx_type const * const m_edgeList;
    wgt_type const * const m_edgeWeight;
};


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

    inline Iterator begin() const noexcept
    {
      return Iterator(m_begin, m_edgeList, m_edgeWeight);
    }

    inline Iterator end()
    {
      return Iterator(m_end, m_edgeList, m_edgeWeight);
    }
  
  private:
    adj_type const m_begin;
    adj_type const m_end;
    vtx_type const * const m_edgeList;
    wgt_type const * const m_edgeWeight;
};




class Vertex
{
  public:
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


    inline vtx_type getID() const noexcept
    {
      return m_index;
    }


    inline wgt_type getWeight() const noexcept
    {
      return m_vertexWeight[m_index];
    }


    inline EdgeSet getEdges() const noexcept
    {
      return EdgeSet(m_edgePrefix[m_index], m_edgePrefix[m_index+1], \
          m_edgeList, m_edgeWeight);
    }


  private:
    vtx_type const m_index;
    wgt_type const * const m_vertexWeight;
    adj_type const * const m_edgePrefix;
    vtx_type const * const m_edgeList;
    wgt_type const * const m_edgeWeight;
};


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

    inline Iterator begin() const noexcept
    {
      return Iterator(m_begin, m_weight, m_edgePrefix, m_edgeList, \
          m_edgeWeight);
    }

    inline Iterator end() const noexcept
    {
      return Iterator(m_end, m_weight, m_edgePrefix, m_edgeList, \
          m_edgeWeight);
    }
  
  private:
    vtx_type const m_begin;
    vtx_type const m_end;
    wgt_type const * const m_weight;
    adj_type const * const m_edgePrefix;
    vtx_type const * const m_edgeList;
    wgt_type const * const m_edgeWeight;
};




class ConstantGraph
{
  public:
    /**
    * @brief Create a new constant graph.
    *
    * @param numVertices The number of vertices in the graph.
    * @param numEdges The number of edges in the graph.
    * @param edgePrefix The prefixsum of the number of edges per vertex. This
    * must be of length numVertices+1. If this is null, then memory is
    * allocated for it, and will be free'd when the object is deconstructed.
    * @param edgeList The list of edges per vertex. This must be of length the
    * number of edges in the graph (counted in each direction). If this is
    * null, then the memory is allocated for it, and will be free'd when the
    * object is deconstructed.
    * @param vertexWeight The weight for each vertex in the graph. 
    * @param edgeWeight The weight for each edge in each direction.
    * @param data A pointer to an object which owns data to be free'd with this
    * graph.
    */
    ConstantGraph(
        vtx_type numVertices,
        adj_type numEdges,
        adj_type const * edgePrefix,
        vtx_type const * edgeList,
        wgt_type const * vertexWeight,
        wgt_type const * edgeWeight,
        IAllocatedData * data = nullptr);


    /**
    * @brief The move constructor.
    *
    * @param lhs The graph to move.
    */
    ConstantGraph(
        ConstantGraph && lhs) noexcept;


    /**
    * @brief Destructor.
    */
    ~ConstantGraph();


    /**
    * @brief Get the number of vertices in the graph.
    *
    * @return The number of vertices.
    */
    inline vtx_type getNumVertices() const noexcept
    {
      return m_numVertices;
    }

    /**
    * @brief Get the number of edges in the graph (counted in each direction).
    *
    * @return The number of edges.
    */
    inline adj_type getNumEdges() const noexcept
    {
      return m_numEdges;
    }

    /**
    * @brief Get the total vertex weight in the graph.
    *
    * @return The total weight.
    */
    inline wgt_type getTotalVertexWeight() const noexcept
    {
      return m_totalVertexWeight; 
    }

    /**
    * @brief Get the total edge weight in the graph.
    *
    * @return The total weight.
    */
    inline wgt_type getTotalEdgeWeight() const noexcept
    {
      return m_totalEdgeWeight;
    }


    /**
    * @brief Get the edge prefixsum array.
    *
    * @return The edge prefixsum array.
    */
    inline adj_type const * getEdgePrefix() const noexcept
    {
      return m_edgePrefix;
    }


    /**
    * @brief Get the edge list array.
    *
    * @return The edge list array.
    */
    inline vtx_type const * getEdgeList() const noexcept
    {
      return m_edgeList;
    }


    /**
    * @brief Get the vertex weight array.
    *
    * @return The vertex weight array.
    */
    inline wgt_type const * getVertexWeight() const noexcept
    {
      return m_vertexWeight;
    }


    /**
    * @brief Get the edge weight array.
    *
    * @return The edge weight array.
    */
    inline wgt_type const * getEdgeWeight() const noexcept
    {
      return m_edgeWeight;
    }


    /**
    * @brief Get the set of vertices in the graph for traversal. 
    *
    * @return The vertex set.
    */
    inline VertexSet getVertices() const noexcept
    {
      return VertexSet(0, m_numVertices, m_vertexWeight, m_edgePrefix, \
          m_edgeList, m_edgeWeight);
    }


  private:
    vtx_type m_numVertices;
    adj_type m_numEdges;

    wgt_type m_totalVertexWeight;
    wgt_type m_totalEdgeWeight;

    adj_type const * m_edgePrefix;
    vtx_type const * m_edgeList;
    wgt_type const * m_vertexWeight;
    wgt_type const * m_edgeWeight;

    /**
    * @brief Any data to free upon destruction.
    */
    IAllocatedData * m_data;

    // disable copying
    ConstantGraph(
        ConstantGraph const & lhs);
    ConstantGraph & operator=(
        ConstantGraph const & lhs);
};

}



#endif
