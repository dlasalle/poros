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
#include "IAllocatedData.hpp"
#include "Array.hpp"
#include "ConstantGraph.hpp"

namespace dolos
{



class GraphData :
    public IAllocatedData
{
  public:
    /**
    * @brief Allocate new graph data
    *
    * @param numVertices The number of vertices in the graph.
    * @param numEdges The number of edges in the graph.
    */
    GraphData(
        vtx_type numVertices,
        adj_type numEdges);


    /**
    * @brief Move constructor.
    *
    * @param lhs The object to move.
    */
    GraphData(
        GraphData && lhs);


    /**
    * @brief Get the number of vertices in the graph.
    *
    * @return The number of vertices.
    */
    vtx_type getNumVertices() const;


    /**
    * @brief Get the number of edges in the graph (counted in each direction).
    *
    * @return The number of edges.
    */
    adj_type getNumEdges() const;


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
    adj_type * getEdgePrefix() noexcept;


    /**
    * @brief Get the pointer to the edge list.
    *
    * @return The pointer.
    */
    vtx_type * getEdgeList() noexcept;


    /**
    * @brief Get the pointer to the vertex weights.
    *
    * @return The pointer.
    */
    wgt_type * getVertexWeight() noexcept;


    /**
    * @brief Get the pointer to the edge weights.
    *
    * @return The pointer.
    */
    wgt_type * getEdgeWeight() noexcept;


    /**
    * @brief Get the pointer to the edge prefix.
    *
    * @return The pointer.
    */
    adj_type const * getEdgePrefix() const noexcept;


    /**
    * @brief Get the pointer to the edge list.
    *
    * @return The pointer.
    */
    vtx_type const * getEdgeList() const noexcept;


    /**
    * @brief Get the pointer to the vertex weights.
    *
    * @return The pointer.
    */
    wgt_type const * getVertexWeight() const noexcept;


    /**
    * @brief Get the pointer to the edge weights.
    *
    * @return The pointer.
    */
    wgt_type const * getEdgeWeight() const noexcept;


  private:
    Array<adj_type> m_edgePrefix;
    Array<vtx_type> m_edgeList;
    Array<wgt_type> m_vertexWeight;
    Array<wgt_type> m_edgeWeight;

    // prevent copying
    GraphData(
        GraphData const & lhs);
    GraphData & operator=(
        GraphData const & lhs);

};


}

#endif
