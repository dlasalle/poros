/**
* @file TwoStepGraphBuilder.hpp
* @brief The TwoStepGraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-12
*/




#ifndef DOLOS_SRC_GRAPHBUILDER_HPP
#define DOLOS_SRC_GRAPHBUILDER_HPP


#include "Base.hpp"
#include "graph/ConstantGraph.hpp"

#include <vector>

namespace dolos
{


class TwoStepGraphBuilder
{
  public:
    enum {
      PHASE_START,
      PHASE_VERTICES,
      PHASE_EDGES
    };


    /**
    * @brief Create a new graph builder.
    */
    TwoStepGraphBuilder();


    /**
    * @brief Set the number of vertices in the graph.
    *
    * @param numVertices The number of vertices in the graph.
    */
    void setNumVertices(
        vtx_type numVertices);


    /**
    * @brief Move onto the vertex insertion phase. SetNumVertices must have
    * been called.
    */
    void beginVertexPhase();


    /**
    * @brief Move onto the edge insertion phase. The number of edges for each
    * vertex must have been set through either setVertexNumEdges() or
    * incVertexNumEdges(), and vertex weight must have been set via
    * setVertexWeight() already.
    */
    void beginEdgePhase();


    /**
    * @brief Build the graph. This resets the builder to its initial state.
    *
    * @return The built graph.
    */
    ConstantGraph finish();


    /**
    * @brief Set the number of edges this vertex will have.
    *
    * @param vertex The vertex.
    * @param numEdges The number of edges.
    */
    inline void setVertexNumEdges(
        vtx_type const vertex,
        adj_type const numEdges) noexcept
    {
      ASSERT_EQUAL(m_phase, PHASE_VERTICES);

      ASSERT_LESS(vertex, m_edgePrefix.size());
      ASSERT_LESS(numEdges, m_numVertices);
      m_edgePrefix[vertex] = numEdges;
    }


    /**
    * @brief Increase the number of edges this vertex will have by one. 
    *
    * @param vertex The vertex.
    */
    inline void incVertexNumEdges(
        vtx_type const vertex) noexcept
    {
      ASSERT_EQUAL(m_phase, PHASE_VERTICES);

      ASSERT_LESS(vertex, m_edgePrefix.size());

      ++m_edgePrefix[vertex];

      // every vertex must be connected to at most n-1 vertices.
      ASSERT_LESS(m_edgePrefix[vertex], m_numVertices);
    }


    /**
    * @brief Set the weight of an individual vertex.
    *
    * @param vertex The vertex to set the weight of.
    * @param weight The weight of the vertex.
    */
    inline void setVertexWeight(
        vtx_type const vertex,
        wgt_type const weight) noexcept
    {
      ASSERT_EQUAL(m_phase, PHASE_VERTICES);

      m_vertexWeight[vertex] = weight;
    }


    /**
    * @brief Add an edge to a given vertex.
    *
    * @param vertex The vertex to add an edge to.
    * @param dest The vertex at the other end of the edge.
    * @param weight The weight of the edge.  
    */
    inline void addEdgeToVertex(
        vtx_type const vertex,
        vtx_type const dest,
        wgt_type const weight) noexcept
    {
      ASSERT_EQUAL(m_phase, PHASE_EDGES);

      ASSERT_LESS(vertex, m_numVertices);
      ASSERT_LESS(dest, m_numVertices);

      adj_type const index = m_edgePrefix[vertex+1]++;
      m_edgeList[index] = dest;
      m_edgeWeight[index] = weight;
    }


  private:
    int m_phase;
    vtx_type m_numVertices;
    adj_type m_numEdges;
    std::vector<adj_type> m_edgePrefix;
    std::vector<vtx_type> m_edgeList;
    std::vector<wgt_type> m_vertexWeight;
    std::vector<wgt_type> m_edgeWeight;

    // prevent copying
    TwoStepGraphBuilder(
        TwoStepGraphBuilder const & lhs) = delete;
    TwoStepGraphBuilder & operator=(
        TwoStepGraphBuilder const & lhs) = delete;



};


}

#endif

