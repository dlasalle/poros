/**
* @file TwoWayConnectivityBuilder.hpp
* @brief The TwoWayConnectivity class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-12-11
*/



#ifndef POROS_SRC_TWOWAYCONNECTIVITYBUILDER_HPP
#define POROS_SRC_TWOWAYCONNECTIVITYBUILDER_HPP

#include "partition/TwoWayConnectivity.hpp"

namespace poros
{


class TwoWayConnectivityBuilder
{
  public:
    using vertex_struct = TwoWayConnectivity::vertex_struct;

    /**
    * @brief Create a new TwoWayConnectivity object.
    */
    TwoWayConnectivityBuilder();

    /**
    * @brief Begin building a connectivity with the given number of vertices.
    *
    * @param numVertices The number of vertices in the new connectivity object.
    */
    void begin(
        vtx_type numVertices);

    /**
    * @brief Set the internal connectivity of the given vertex.
    *
    * @param vertex The vertex.
    * @param weight The weight of edges connecting to this partition.
    */
    void setInternalConnectivityOf(
        Vertex const vertex,
        wgt_type const weight) noexcept
    {
      ASSERT_LESS(vertex.index, m_connectivity.size());
      m_connectivity[vertex.index].internal = weight;
    }

    /**
    * @brief Set the external connectivity of the given vertex.
    *
    * @param vertex The vertex.
    * @param weight The weight of edges connecting to the other partition.
    */
    void setExternalConnectivityOf(
        Vertex const vertex,
        wgt_type const weight) noexcept
    {
      ASSERT_LESS(vertex.index, m_connectivity.size());
      m_connectivity[vertex.index].external = weight;
    }

    /**
    * @brief Finish building this TwoWayConnectivity.
    *
    * @return The build object.
    */
    TwoWayConnectivity finish();

  private:
    sl::Array<vertex_struct> m_connectivity;
};

}


#endif

