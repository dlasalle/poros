/**
* @file Graph.hpp
* @brief The Graph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-06
*/



#ifndef POROS_SRC_GRAPH_HPP
#define POROS_SRC_GRAPH_HPP


#include "Base.hpp"
#include "util/IAllocatedData.hpp"
#include "graph/EdgeSet.hpp"
#include "graph/VertexSet.hpp"
#include "solidutils/ConstArray.hpp"
#include "solidutils/Debug.hpp"
#include <cstdlib>


namespace poros
{


class Graph
{
  public:
    /**
    * @brief Create a new constant graph, where the memory for it is owned
    * internally.
    *
    * @param edgePrefix The prefixsum of the number of edges per vertex. This
    * must be of length numVertices+1. If this is null, then memory is
    * allocated for it, and will be free'd when the object is deconstructed.
    * @param edgeList The list of edges per vertex. This must be of length the
    * number of edges in the graph (counted in each direction). If this is
    * null, then the memory is allocated for it, and will be free'd when the
    * object is deconstructed.
    * @param vertexWeight The weight for each vertex in the graph. 
    * @param edgeWeight The weight for each edge in each direction.
    */
    Graph(
        sl::ConstArray<adj_type> edgePrefix,
        sl::ConstArray<vtx_type> edgeList,
        sl::ConstArray<wgt_type> vertexWeight,
        sl::ConstArray<wgt_type> edgeWeight);


    /**
    * @brief Create a new constant graph, where the memory for it is owned
    * externally.
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
    */
    Graph(
        vtx_type numVertices,
        adj_type numEdges,
        adj_type const * edgePrefix,
        vtx_type const * edgeList,
        wgt_type const * vertexWeight,
        wgt_type const * edgeWeight);


    /**
    * @brief The move constructor.
    *
    * @param rhs The graph to move.
    */
    Graph(
        Graph && rhs) noexcept;


    /**
    * @brief Get the number of vertices in the graph.
    *
    * @return The number of vertices.
    */
    vtx_type numVertices() const noexcept
    {
      return m_numVertices;
    }


    /**
    * @brief Get the number of edges in the graph (counted in each direction).
    *
    * @return The number of edges.
    */
    adj_type numEdges() const noexcept
    {
      return m_numEdges;
    }


    /**
    * @brief Get the total vertex weight in the graph.
    *
    * @return The total weight.
    */
    wgt_type getTotalVertexWeight() const noexcept
    {
      return m_totalVertexWeight; 
    }


    /**
    * @brief Get the total edge weight in the graph.
    *
    * @return The total weight.
    */
    wgt_type getTotalEdgeWeight() const noexcept
    {
      return m_totalEdgeWeight;
    }


    /**
    * @brief Get the edge prefixsum array.
    *
    * @return The edge prefixsum array.
    */
    adj_type const * getEdgePrefix() const noexcept
    {
      return m_edgePrefix.data();
    }


    /**
    * @brief Get the edge list array.
    *
    * @return The edge list array.
    */
    vtx_type const * getEdgeList() const noexcept
    {
      return m_edgeList.data();
    }


    /**
    * @brief Get the weight of an individual vertex.
    *
    * @param vertex The vertex.
    *
    * @return The weight of the vertex.
    */
    wgt_type getVertexWeight(
        vtx_type const vertex) const noexcept
    {
      return m_vertexWeight[vertex];
    }


    /**
    * @brief Get the vertex weight array.
    *
    * @return The vertex weight array.
    */
    wgt_type const * getVertexWeight() const noexcept
    {
      return m_vertexWeight.data();
    }


    /**
    * @brief Get the edge weight array.
    *
    * @return The edge weight array.
    */
    wgt_type const * getEdgeWeight() const noexcept
    {
      return m_edgeWeight.data();
    }


    /**
    * @brief Get the set of vertices in the graph for traversal. 
    *
    * @return The vertex set.
    */
    VertexSet vertices() const noexcept
    {
      return VertexSet(0, m_numVertices);
    }


    /**
    * @brief Get the set of edges in the graph for traversal.
    *
    * @return The edge set.
    */
    EdgeSet edges() const noexcept
    {
      return EdgeSet(0, m_numEdges, m_edgeList.data(), m_edgeWeight.data());
    }


    /**
    * @brief Get the set of edges of the vertex for traversal.
    *
    * @param vertex The vertex.
    *
    * @return The edge set of the vertex.
    */
    EdgeSet edgesOf(
        Vertex const vertex) const noexcept
    {
      vtx_type const v = vertex.index;
      return EdgeSet(m_edgePrefix[v], m_edgePrefix[v+1], m_edgeList.data(), \
          m_edgeWeight.data());
    }

    /**
    * @brief Get the degree of a vertex.
    *
    * @param v The vertex.
    *
    * @return The degree of the vertex.
    */
    vtx_type degreeOf(
        Vertex const v) const noexcept
    {
      return m_edgePrefix[v.index+1] - m_edgePrefix[v.index];
    }

    /**
    * @brief Get the destination of a given edge.
    *
    * @param e The edge.
    *
    * @return The destination vertex.
    */
    Vertex destinationOf(
        Edge const e) const noexcept
    {
      return Vertex::make(m_edgeList[e.index]);
    }

    /**
    * @brief Get the weight of the given edge.
    *
    * @param e The edge.
    *
    * @return The weight.
    */
    wgt_type weightOf(
        Edge const e) const noexcept
    {
      return m_edgeWeight[e.index];
    }

    /**
    * @brief Get the weight of the given vertex.
    *
    * @param v The vertex.
    *
    * @return The weight.
    */
    wgt_type weightOf(
        Vertex const v) const noexcept
    {
      return m_vertexWeight[v.index];
    }

    /**
    * @brief Check if the graph has uniform edge weights.
    *
    * @return True if the edge weights are all equal.
    */
    bool hasUniformEdgeWeight() const noexcept
    {
      return m_uniformEdgeWeight;
    }

    /**
    * @brief Check if the graph has uniform vertex weights.
    *
    * @return True if the vertex weights are all equal.
    */
    bool hasUniformVertexWeight() const noexcept
    {
      return m_uniformVertexWeight;
    }

   
    #ifndef NDEBUG
    /**
    * @brief Check if this graph is internally coherent.
    *
    * @return True if the graph is valid.
    */
    bool isValid() const;
    #endif

  private:
    bool m_uniformEdgeWeight;
    bool m_uniformVertexWeight;

    vtx_type m_numVertices;
    adj_type m_numEdges;

    wgt_type m_totalVertexWeight;
    wgt_type m_totalEdgeWeight;

    sl::ConstArray<adj_type> m_edgePrefix;
    sl::ConstArray<vtx_type> m_edgeList;
    sl::ConstArray<wgt_type> m_vertexWeight;
    sl::ConstArray<wgt_type> m_edgeWeight;

    // disable copying
    Graph(
        Graph const & lhs) = delete;
    Graph & operator=(
        Graph const & lhs) = delete;
};


}


#endif
