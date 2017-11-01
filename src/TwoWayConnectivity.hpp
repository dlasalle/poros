/**
* @file TwoWayConnectivity.hpp
* @brief The TwoWayConnectivity class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-19
*/




#ifndef DOLOS_SRC_TWOWAYCONNECTIVITY_HPP
#define DOLOS_SRC_TWOWAYCONNECTIVITY_HPP


#include "Array.hpp"
#include "Base.hpp"
#include "ConstantGraph.hpp"
#include "Partitioning.hpp"
#include "FixedSet.hpp"


namespace dolos
{


class TwoWayConnectivity
{
  public:
    struct vertex_struct
    {
      wgt_type external;
      wgt_type internal;
    };

  
    /**
    * @brief Create a new two-way connectivity.
    *
    * @param graph The graph.
    * @param partitioning The partitioning.
    */
    TwoWayConnectivity(
        ConstantGraph const * graph,
        Partitioning * partitioning);


    /**
    * @brief Move a vertex to the opposite partition. This updates the
    * partitioning as well as the connectivity.
    *
    * @param vertex The vertex to move.
    */
    inline void move(
        vtx_type const vertex)
    {
      wgt_diff_type const delta = getVertexDelta(vertex);

      pid_type const home = m_partitioning->getAssignment(vertex);
      pid_type const dest = (home + 1) % NUM_BISECTION_PARTS;
      
      m_partitioning->move(vertex, dest);
      m_partitioning->addCutEdgeWeight(delta);

      // flip our connectivity
      std::swap(m_connectivity[vertex].internal, \
          m_connectivity[vertex].external);

      // update neighbor connectivity
      for (Edge const & edge : m_graph->getEdges(vertex)) {
        vtx_type const u = edge.getVertex();
        pid_type const other = m_partitioning->getAssignment(u);

        // branchless calculation
        wgt_diff_type const flow = ((other ^ home)<<1) - 1;
        m_connectivity[u].internal += flow*edge.getWeight();
        m_connectivity[u].external -= flow*edge.getWeight();
      }
    }


    /**
    * @brief Get the delta that would result from moving this vertex (negative
    * means fewer edges would be cut).
    *
    * @param vertex The vertex.
    *
    * @return The edge weight delta.
    */
    inline wgt_diff_type getVertexDelta(
        vtx_type const vertex) const noexcept
    {
      ASSERT_LESS(vertex, m_connectivity.size());
      return static_cast<wgt_diff_type>(m_connectivity[vertex].internal) - \
          static_cast<wgt_diff_type>(m_connectivity[vertex].external);
    }


    /**
    * @brief Get the set of border vertices for the given partition.
    *
    * @param side The partition.
    *
    * @return The set of border vertices.
    */
    inline vtx_type const * getBorderVertices(
        pid_type const side) const noexcept
    {
      ASSERT_LESS(side, NUM_BISECTION_PARTS);

      return m_border[side].data(); 
    }


    /**
    * @brief Get the number of border vertices for a given partition.
    *
    * @param side The partition.
    *
    * @return The set of border vertices.
    */
    inline vtx_type getNumBorderVertices(
        pid_type const side) const noexcept
    {
      ASSERT_LESS(side, NUM_BISECTION_PARTS);

      return m_border[side].size(); 
    }


  private:
    solidutils::FixedSet<vtx_type> m_border[NUM_BISECTION_PARTS];
    solidutils::Array<vertex_struct> m_connectivity;
    ConstantGraph const * const m_graph;
    Partitioning * const m_partitioning;


    // disable copying
    TwoWayConnectivity(
        TwoWayConnectivity const & rhs);
    TwoWayConnectivity & operator=(
        TwoWayConnectivity const & rhs);
};

}

#endif
