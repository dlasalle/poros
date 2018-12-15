/**
* @file GraphHandle.hpp
* @brief The GraphHandle class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-11-14
*/


#ifndef POROS_SRC_GRAPHHANDLE_HPP
#define POROS_SRC_GRAPHHANDLE_HPP



#include "Graph.hpp"

#include <memory>


namespace poros
{


class GraphHandle
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
    GraphHandle(
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
    GraphHandle(
        vtx_type numVertices,
        adj_type numEdges,
        adj_type const * edgePrefix,
        vtx_type const * edgeList,
        wgt_type const * vertexWeight,
        wgt_type const * edgeWeight);


    /**
    * @brief Move a graph into this handle.
    *
    * @param rhs The graph to move.
    */
    GraphHandle(
        Graph rhs);


    /**
    * @brief Pointer operator.
    *
    * @return The underlying graph.
    */
    Graph * operator->() noexcept
    {
      return m_graph.get();
    }


    /**
    * @brief Pointer operator.
    *
    * @return The underlying graph.
    */
    Graph const * operator->() const noexcept
    {
      return m_graph.get();
    }


    /**
    * @brief Get a pointer to the graph.
    *
    * @return The pointer.
    */
    Graph * get() noexcept
    {
      return m_graph.get();
    }
    

    /**
    * @brief Get a pointer to the graph.
    *
    * @return The pointer.
    */
    Graph const * get() const noexcept
    {
      return m_graph.get();
    }
 

  private:
    std::shared_ptr<Graph> m_graph;
};

}

#endif
