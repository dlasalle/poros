/**
 * @file MutableGraph.hpp
 * @brief The MutableGraph class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#ifndef DOLOS_SRC_MUTABLEGRAPH_HPP
#define DOLOS_SRC_MUTABLEGRAPH_HPP


#include "Base.hpp"
#include "MutableArray.hpp"

namespace dolos
{

class MutableGraph
{
  public:
    /**
    * @brief Create a new graph.
    *
    * @param nvtxs The number of vertices in the graph.
    * @param nedges The number of edges in the graph.
    * @param edgePrefix The prefixsum of the number of edges per vertex. This
    * must be of length nvtxs+1. If this is null, then memory is allocated for
    * it, and will be free'd when the object is deconstructed.
    * @param edgeList The list of edges per vertex. This must be of length the
    * number of edges in the graph (counted in each direction). If this is
    * null, then the memory is allocated for it, and will be free'd when the
    * object is deconstructed.
    * @param vertexWeight The weight for each vertex in the graph. 
    * @param edgeWeight
    */
    MutableGraph(
        vtx_type nvtxs,
        adj_type nedges,
        adj_type * const edgePrefix = nullptr,
        vtx_type * const edgeList = nullptr,
        wgt_type * const vertexWeight = nullptr,
        wgt_type * const edgeWeight = nullptr);


    /**
    * @brief Create a constant version of this graph and destroy this one.
    * Calling any function after this one is considered undefined behavior.
    *
    * @return The constant version of the graph.
    */
    ConstantGraph finalize();

    /**
    * @brief Get the number of vertices in the graph.
    *
    * @return The number of vertices.
    */
    vtx_type getNumVertices() const noexcept
    {
      return m_numVertices;
    }

    /**
    * @brief Get the number of edges in the graph (counted in each direction).
    *
    * @return The number of edges.
    */
    adj_type getNumEdges() const noexcept
    {
      return m_numEdges;
    }

    /**
    * @brief Get the edge prefixsum array.
    *
    * @return The edge prefixsum array.
    */
    adj_type * getEdgePrefix();

    /**
    * @brief Get the edge list array.
    *
    * @return The edge list array.
    */
    vtx_type * getEdgeList();

    /**
    * @brief Get the vertex weight array.
    *
    * @return The vertex weight array.
    */
    wgt_type * getVertexWeight();

    /**
    * @brief Get the edge weight array.
    *
    * @return The edge weight array.
    */
    wgt_type * getEdgeWeight();


  private:
    vtx_type m_numVertices;
    adj_type m_numEdges;

    MutableArray<wgt_type> m_vertexWeight;
    MutableArray<adj_type> m_edgePrefix;
    MutableArray<vtx_type> m_edgeList;
    MutableArray<wgt_type> m_edgeWeight;
};

}


#endif
