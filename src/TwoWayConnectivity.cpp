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
  m_border{graph->getNumVertices(), graph->getNumVertices()},
  m_connectivity(graph->getNumVertices())
{
  // populate connectivity vector
  for (Vertex const & vertex : graph->getVertices()) {
    vertex_struct pair{0, 0};
    vtx_type const v = vertex.getIndex();
    pid_type const home = partitioning->getAssignment(v);
    for (Edge const & edge : graph->getEdges()) {
      vtx_type const u = edge.getVertex();
      pid_type const other = partitioning->getAssignment(u);
      if (other == home) {
        pair.internal += edge.getWeight();
      } else {
        pair.external += edge.getWeight();
      }
    }

    if (pair.external > 0) {
      m_border[home].add(v);
    }
  }
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


  
}
