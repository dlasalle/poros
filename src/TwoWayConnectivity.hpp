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


#include "FixedSet.hpp"
#include "Array.hpp"
#include "Base.hpp"
#include "ConstantGraph.hpp"
#include "Partitioning.hpp"


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
    void move(
        vtx_type const vertex)
    {
      wgt_diff_type const delta = vertex_delta(vertex);

      pid_type const home = partitioning->getAssignment(vertex);
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


  private:
    FixedSet<vtx_type> m_border[NUM_BISECTION_PARTS];
    Array<vertex_struct> m_connectivity;
    ConstantGraph const * const m_graph;
    Partitioning * const m_partitioning;



    /**
    * @brief Get the delta that would result from moving this vertex (negative
    * means fewer edges would be cut).
    *
    * @param vertex The vertex.
    *
    * @return The edge weight delta.
    */
    wgt_diff_type vertex_delta(
        vtx_type const vertex) const noexcept
    {
      ASSERT_LESS(vertex, m_connectivity.size());
      return static_cast<wgt_diff_type>(m_connectivity[vertex].internal) - \
          static_cast<wgt_diff_type>(m_connectivity[vertex].external);
    }
};

}

#endif
