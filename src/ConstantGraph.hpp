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


#include "Base.hpp"
#include "IAllocatedData.hpp"
#include "EdgeSet.hpp"
#include "VertexSet.hpp"
#include <cstdlib>
#include "solidutils/Debug.hpp"


namespace dolos
{


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
    * @brief Get the weight of an individual vertex.
    *
    * @param vertex The vertex.
    *
    * @return The weight of the vertex.
    */
    inline wgt_type getVertexWeight(
        vtx_type const vertex) const noexcept
    {
      return m_vertexWeight[vertex];
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


    /**
    * @brief Get the set of edges in the graph for traversal.
    *
    * @return The edge set.
    */
    inline EdgeSet getEdges() const noexcept
    {
      return EdgeSet(0, m_numEdges, m_edgeList, m_edgeWeight);
    }


    /**
    * @brief Get the set of edges of the vertex for traversal.
    *
    * @param v The vertex.
    *
    * @return The edge set of the vertex.
    */
    inline EdgeSet getEdges(
        vtx_type const v) const noexcept
    {
      return EdgeSet(m_edgePrefix[v], m_edgePrefix[v+1], m_edgeList, \
          m_edgeWeight);
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
