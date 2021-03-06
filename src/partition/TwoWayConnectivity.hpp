/**
* @file TwoWayConnectivity.hpp
* @brief The TwoWayConnectivity class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-19
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/




#ifndef POROS_SRC_TWOWAYCONNECTIVITY_HPP
#define POROS_SRC_TWOWAYCONNECTIVITY_HPP


#include "Base.hpp"
#include "graph/Graph.hpp"
#include "Partitioning.hpp"
#include "solidutils/FixedSet.hpp"
#include "solidutils/Array.hpp"


namespace poros
{


class TwoWayConnectivity
{
  public:
    using BorderSet = sl::FixedSet<vtx_type>;

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

    struct vertex_struct
    {
      wgt_type external;
      wgt_type internal;
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
      return -(static_cast<int>((destVertexA ^ homeVertexB)<<1)-1);
    }


    /**
    * @brief Create a TwoWayConnectivity from a graph and partitioning.
    *
    * @param graph The graph that is partitioned.
    * @param partitioning The partitioning.
    *
    * @return The TwoWayConnectivity.
    *
    * @throw An exception if the partitioning is not a bisection.
    */
    static TwoWayConnectivity fromPartitioning(
        Graph const * graph,
        Partitioning const * partitioning);


    /**
    * @brief Create a new two-way connectivity from the internal/external
    * weights associated with each vertex.
    *
    * @param connectivity The weights.
    */
    TwoWayConnectivity(
        sl::Array<vertex_struct> connectivity);


    /**
    * @brief Deleted copy constructor.
    *
    * @param rhs The object to copy.
    */
    TwoWayConnectivity(
        TwoWayConnectivity const & rhs) = delete;


    /**
    * @brief Deleted copy assignment operator.
    *
    * @param rhs The object to copy.
    *
    * @return This object.
    */
    TwoWayConnectivity & operator=(
        TwoWayConnectivity const & rhs) = delete;


    /**
    * @brief Default implementation of the move constructor.
    *
    * @param rhs The connectivity to move.
    */
    TwoWayConnectivity(
        TwoWayConnectivity && rhs) = default;


    /**
    * @brief Get the set of border vertices.
    *
    * @return The set of border vertices.
    */
    BorderSet const * getBorderVertexSet() const noexcept;


    /**
    * @brief Get the set of border vertices.
    *
    * @return The set of border vertices.
    */
    BorderSet * getBorderVertexSet() noexcept;


    /**
    * @brief Move a vertex to the opposite partition. 
    *
    * @param vertex The vertex to move.
    *
    * @return The state of the vertex in the bodrer (the border_status_enum). 
    */
    int move(
        Vertex const vertex) noexcept
    {
      // flip our connectivity
      vtx_type const index = vertex.index;
      std::swap(m_connectivity[index].internal, \
          m_connectivity[index].external);

      return updateBorderStatus(index);
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
    int updateNeighbor(
        vtx_type const neighbor,
        wgt_type const edgeWeight,
        int const direction) noexcept
    {
      // ensure it is 1 or -1
      ASSERT_EQUAL(1, direction*direction);

      // branchless calculation -- flow will be 1 when the vertex is being
      // moved to the same partition as this one, and -1 when it is being moved
      // away.
      wgt_diff_type const flow = static_cast<wgt_diff_type>(direction);
      m_connectivity[neighbor].internal += flow*edgeWeight;
      m_connectivity[neighbor].external -= flow*edgeWeight;

      return updateBorderStatus(neighbor);
    }


    /**
    * @brief Get the delta that would result from moving this vertex (negative
    * means fewer edges would be cut).
    *
    * @param vertex The vertex.
    *
    * @return The edge weight delta.
    */
    wgt_diff_type getVertexDelta(
        Vertex const vertex) const noexcept
    {
      return getVertexDelta(vertex.index);
    }


    /**
    * @brief Get the delta that would result from moving this vertex (negative
    * means fewer edges would be cut).
    *
    * @param vertex The vertex.
    *
    * @return The edge weight delta.
    */
    wgt_diff_type getVertexDelta(
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
    bool isInBorder(
        Vertex const vertex) const noexcept
    {
      return m_border.has(vertex.index);
    }


    /**
    * @brief Check whether or not a vertex is in the border.
    *
    * @param vertex The vertex.
    *
    * @return Whether or not it is in the border. 
    */
    bool isInBorder(
        vtx_type const vertex) const noexcept
    {
      return m_border.has(vertex);
    }

    
    /**
    * @brief Get the internal connectivity of the given vertex.
    *
    * @param v The vertex.
    *
    * @return The weight of edges connecting this vertex to other vertices
    * in the partition in which it resides.
    */
    wgt_type internalConnectivityOf(
        Vertex const v) const noexcept
    {
      return m_connectivity[v.index].internal;
    }


    /**
    * @brief Get the external connectivity of the given vertex.
    *
    * @param v The vertex.
    *
    * @return The weight of edges connecting this vertex to other vertices
    * in a partition other than the one in which this vertex resides.
    */
    wgt_type externalConnectivityOf(
        Vertex const v) const noexcept
    {
      return m_connectivity[v.index].external;
    }


    /**
    * @brief Verify that this two way connectivity is correct.
    *
    * @param graph The graph.
    * @param part The partitioning.
    *
    * @return True if this connectivity is correct, false otherwise.
    */
    bool verify(
        Graph const * graph,
        Partitioning const * part) const;


  private:
    sl::FixedSet<vtx_type> m_border;
    sl::Array<vertex_struct> m_connectivity;

    /**
    * @brief Create a string of the connectivity of the vertex.
    *
    * @param v The vertex.
    *
    * @return The string.
    */
    std::string getVertexDegreeString(
        vtx_type const v) const;

    /**
    * @brief Update the border status of vertex (whether it is in it or not).
    *
    * @param vertex The vertex.
    *
    * @return The state of the vertex in the bodrer (the border_status_enum). 
    */
    inline int updateBorderStatus(
        vtx_type const vertex) noexcept
    {
      if (m_border.has(vertex)) {
        if (m_connectivity[vertex].external == 0) {
          // remove from boundary
          m_border.remove(vertex);
          return BORDER_REMOVED;
        } else {
          return BORDER_STILLIN; 
        } 
      } else {
        if (m_connectivity[vertex].external > 0) {
          // insert into boundary
          m_border.add(vertex);
          return BORDER_ADDED;
        } else {
          return BORDER_STILLOUT; 
        } 
      }

    }
};

}

#endif
