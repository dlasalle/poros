/**
* @file GraphData.hpp
* @brief The GraphData class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/




#ifndef DOLOS_SRC_GRAPHDATA_HPP
#define DOLOS_SRC_GRAPHDATA_HPP

#include "Base.hpp"
#include "graph/ConstantGraph.hpp"
#include "util/IAllocatedData.hpp"
#include "solidutils/Array.hpp"

namespace dolos
{



class GraphData :
    public IAllocatedData
{
  public:
    /**
    * @brief Allocate new graph data.
    *
    * @param numVertices The number of vertices in the graph.
    * @param numEdges The number of edges in the graph.
    */
    GraphData(
        vtx_type numVertices,
        adj_type numEdges);


    /**
    * @brief Create a new graph data from an existing set of arrays.
    *
    * @param edgePrefix The edge prefix array.
    * @param edgeList The edge list array.
    * @param vertexWeight The vertex weight array.
    * @param edgeWeight The edge weight array.
    */
    GraphData(
        sl::Array<adj_type> * edgePrefix,
        sl::Array<vtx_type> * edgeList,
        sl::Array<wgt_type> * vertexWeight,
        sl::Array<wgt_type> * edgeWeight);


    /**
    * @brief Move constructor.
    *
    * @param lhs The object to move.
    */
    GraphData(
        GraphData && lhs) noexcept;


    /**
    * @brief Get the number of vertices in the graph.
    *
    * @return The number of vertices.
    */
    vtx_type numVertices() const;


    /**
    * @brief Get the number of edges in the graph (counted in each direction).
    *
    * @return The number of edges.
    */
    adj_type numEdges() const;


    /**
    * @brief Turn the graph data into a graph. This is a destructive operation.
    *
    * @return The graph.
    */
    ConstantGraph toGraph();


    /**
    * @brief Set all vertex weights to 1.
    */
    void setUnitVertexWeight() noexcept;


    /**
    * @brief Make all edge weights 1.
    */
    void setUnitEdgeWeight() noexcept;


    /**
    * @brief Get the pointer to the edge prefix.
    *
    * @return The pointer.
    */
    adj_type * edgePrefix() noexcept;


    /**
    * @brief Get the pointer to the edge list.
    *
    * @return The pointer.
    */
    vtx_type * edgeList() noexcept;


    /**
    * @brief Get the pointer to the vertex weights.
    *
    * @return The pointer.
    */
    wgt_type * vertexWeight() noexcept;


    /**
    * @brief Get the pointer to the edge weights.
    *
    * @return The pointer.
    */
    wgt_type * edgeWeight() noexcept;


    /**
    * @brief Get the pointer to the edge prefix.
    *
    * @return The pointer.
    */
    adj_type const * edgePrefix() const noexcept;


    /**
    * @brief Get the pointer to the edge list.
    *
    * @return The pointer.
    */
    vtx_type const * edgeList() const noexcept;


    /**
    * @brief Get the pointer to the vertex weights.
    *
    * @return The pointer.
    */
    wgt_type const * vertexWeight() const noexcept;


    /**
    * @brief Get the pointer to the edge weights.
    *
    * @return The pointer.
    */
    wgt_type const * edgeWeight() const noexcept;




  private:
    sl::Array<adj_type> m_edgePrefix;
    sl::Array<vtx_type> m_edgeList;
    sl::Array<wgt_type> m_vertexWeight;
    sl::Array<wgt_type> m_edgeWeight;

    // prevent copying
    GraphData(
        GraphData const & lhs);
    GraphData & operator=(
        GraphData const & lhs);

};


}

#endif
