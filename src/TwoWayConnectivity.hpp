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


#include "Base.hpp"
#include "ConstantGraph.hpp"
#include "Partitioning.hpp"
#include "solidutils/FixedSet.hpp"
#include "solidutils/Array.hpp"


namespace dolos
{


class TwoWayConnectivity
{
  public:
    enum move_direction_enum {
      MOVE_TOWARDS = 1,
      MOVE_AWAY = -1
    };

    enum border_status_enum {
      BORDER_ADDED,
      BORDER_REMOVED,
      BORDER_STILLIN,
      BORDER_STILLOUT
    };

    /**
    * @brief Determine the direction enum given the partition a vertex is
    * moving to, and the partition of the other vertex.
    *
    * @param destVertexA The partition the vertex in moving to.
    * @param homeVertexB The partition of one of its neighbors.
    *
    * @return The appropriate value from move_direction_enum.
    */
    static inline int getDirection(
        pid_type const destVertexA,
        pid_type const homeVertexB) noexcept
    {
      return -(((destVertexA ^ homeVertexB)<<1)-1);
    }
        

    /**
    * @brief Create a new two-way connectivity.
    *
    * @param graph The graph.
    * @param partitioning The partitioning.
    */
    TwoWayConnectivity(
        ConstantGraph const * graph,
        Partitioning const * partitioning);


    /**
    * @brief Get the set of border vertices.
    *
    * @return The set of border vertices.
    */
    sl::FixedSet<vtx_type> const * getBorderVertexSet() const noexcept;


    /**
    * @brief Get the set of border vertices.
    *
    * @return The set of border vertices.
    */
    sl::FixedSet<vtx_type> * getBorderVertexSet() noexcept;


    /**
    * @brief Move a vertex to the opposite partition. 
    *
    * @param vertex The vertex to move.
    */
    inline void move(
        vtx_type const vertex) noexcept
    {
      // flip our connectivity
      std::swap(m_connectivity[vertex].internal, \
          m_connectivity[vertex].external);
    }


    /**
    * @brief Update the neighbor of a vertex that is being moved.
    *
    * @param edge The edge connecting the neighbor.
    * @param direction The destination partition of the vertex -- must be a
    * member of the move_direction_enum (1 or -1).
    *
    * @return The state of the vertex in the bodrer (the border_status_enum). 
    */
    inline int updateNeighbor(
        Edge const * const edge,
        int const direction) noexcept
    {
      // ensure it is 1 or -1
      ASSERT_EQUAL(1, direction*direction);

      vtx_type const u = edge->getVertex();

      // branchless calculation -- flow will be 1 when the vertex is being
      // moved to the same partition as this one, and -1 when it is being moved
      // away.
      wgt_diff_type const flow = static_cast<wgt_diff_type>(direction);
      m_connectivity[u].internal += flow*edge->getWeight();
      m_connectivity[u].external -= flow*edge->getWeight();

      if (m_border.has(u)) {
        if (m_connectivity[u].external == 0) {
          // remove from boundary
          m_border.remove(u);
          return BORDER_REMOVED;
        } else {
          return BORDER_STILLIN; 
        } 
      } else {
        if (m_connectivity[u].external > 0) {
          // insert into boundary
          m_border.add(u);
          return BORDER_ADDED;
        } else {
          return BORDER_STILLOUT; 
        } 
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
    * @brief Check whether or not a vertex is in the border.
    *
    * @param vertex The vertex.
    *
    * @return Whether or not it is in the border. 
    */
    inline bool isInBorder(
        vtx_type const vertex) const noexcept
    {
      return m_border.has(vertex);
    }


    /**
    * @brief Verify that this two way connectivity is correct.
    *
    * @param part The partitioning.
    *
    * @return True if this connectivity is correct, false otherwise.
    */
    bool verify(
        Partitioning const * part) const;


  private:
    struct vertex_struct
    {
      wgt_type external;
      wgt_type internal;
    };

 
    sl::FixedSet<vtx_type> m_border;
    sl::Array<vertex_struct> m_connectivity;
    ConstantGraph const * const m_graph;


    // disable copying
    TwoWayConnectivity(
        TwoWayConnectivity const & rhs);
    TwoWayConnectivity & operator=(
        TwoWayConnectivity const & rhs);


    /**
    * @brief Create a string of the connectivity of the vertex.
    *
    * @param v The vertex.
    *
    * @return The string.
    */
    std::string getVertexDegreeString(
        vtx_type const v) const;
};

}

#endif
