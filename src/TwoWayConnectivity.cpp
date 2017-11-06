/**
* @file TwoWayConnectivity.cpp
* @brief Implementation of the TwoWayConnectivity class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-19
*/



#include "TwoWayConnectivity.hpp"



namespace dolos
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


TwoWayConnectivity::TwoWayConnectivity(
    ConstantGraph const * const graph,
    Partitioning const * const partitioning) :
  m_border(graph->getNumVertices()),
  m_connectivity(graph->getNumVertices()),
  m_graph(graph)
{
  // populate connectivity vector
  for (Vertex const & vertex : graph->getVertices()) {
    vertex_struct pair{0, 0};
    vtx_type const v = vertex.getIndex();
    pid_type const home = partitioning->getAssignment(v);
    for (Edge const & edge : vertex.getEdges()) {
      vtx_type const u = edge.getVertex();
      pid_type const other = partitioning->getAssignment(u);
      if (other == home) {
        pair.internal += edge.getWeight();
      } else {
        pair.external += edge.getWeight();
      }
    }

    if (pair.external > 0) {
      m_border.add(v);
    }

    m_connectivity[v] = pair;
  }
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


sl::FixedSet<vtx_type> * TwoWayConnectivity::getBorderVertexSet() noexcept
{
  return &m_border;
}

sl::FixedSet<vtx_type> const * TwoWayConnectivity::getBorderVertexSet()
    const noexcept
{
  return &m_border;
}
  
}
