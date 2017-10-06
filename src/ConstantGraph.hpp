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
#include "ConstantArray.hpp"


namespace dolos
{

class ConstantGraph
{
  public:
    /**
    * @brief Create a new constant graph.
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
    ConstantGraph(
        vtx_type nvtxs,
        adj_type nedges,
        adj_type const * const edgePrefix = nullptr,
        vtx_type const * const edgeList = nullptr,
        wgt_type const * const vertexWeight = nullptr,
        wgt_type const * const edgeWeight = nullptr);

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
    * @brief Get the total vertex weight in the graph.
    *
    * @return The total weight.
    */
    wgt_type getTotalVertexWeight() const
    {
      return m_totalVertexWeight; 
    }

    /**
    * @brief Get the total edge weight in the graph.
    *
    * @return The total weight.
    */
    wgt_type getTotalEdgeWeight() const
    {
      return m_totalEdgeWeight;
    }


    /**
    * @brief Get the edge prefixsum array.
    *
    * @return The edge prefixsum array.
    */
    adj_type const * getEdgePrefix() const;


    /**
    * @brief Get the edge list array.
    *
    * @return The edge list array.
    */
    vtx_type const * getEdgeList() const;


    /**
    * @brief Get the vertex weight array.
    *
    * @return The vertex weight array.
    */
    wgt_type const * getVertexWeight() const;


    /**
    * @brief Get the edge weight array.
    *
    * @return The edge weight array.
    */
    wgt_type const * getEdgeWeight() const;


  private:
    vtx_type m_numVertices;
    adj_type m_numEdges;

    wgt_type m_totalVertexWeight;
    wgt_type m_totalEdgeWeight;

    ConstantArray<wgt_type> m_vertexWeight;
    ConstantArray<adj_type> m_edgePrefix;
    ConstantArray<vtx_type> m_edgeList;
    ConstantArray<wgt_type> m_edgeWeight;

    // disable copying
    ConstantGraph(
        ConstantGraph const & lhs);
    ConstantGraph & operator=(
        ConstantGraph const & lhs);
};

}



#endif
