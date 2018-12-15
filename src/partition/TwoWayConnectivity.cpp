/**
* @file TwoWayConnectivity.cpp
* @brief Implementation of the TwoWayConnectivity class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-19
*/



#include "TwoWayConnectivity.hpp"


namespace poros
{

using vertex_struct = TwoWayConnectivity::vertex_struct;


/******************************************************************************
* HELPER FUCNTIONS ************************************************************
******************************************************************************/

namespace
{

/**
* @brief Check if a vertex should be considered in the boundary given its
* connectivity.
*
* @param v The connectivity of the vertex.
*
* @return True if it should be in the boundary.
*/
bool shouldBeInBorder(
    vertex_struct const v)
{
 return v.external > 0 || v.internal == 0;
}

}


/******************************************************************************
* PRIVATE FUNCTIONS ***********************************************************
******************************************************************************/

std::string TwoWayConnectivity::getVertexDegreeString(
    vtx_type const v) const
{
  std::string str(std::string("Vertex ") + std::to_string(v) + \
      std::string(" (i") + std::to_string(m_connectivity[v].internal) + \
      std::string(":e") + std::to_string(m_connectivity[v].external) + \
      std::string(")"));
  return str;
}


/******************************************************************************
* PUBLIC STATIC METHODS *******************************************************
******************************************************************************/

TwoWayConnectivity TwoWayConnectivity::fromPartitioning(
    Graph const * const graph,
    Partitioning const * const partitioning)
{
  sl::Array<vertex_struct> connectivity(graph->numVertices());

  // populate connectivity vector
  for (Vertex const vertex : graph->vertices()) {
    vertex_struct pair{0, 0};
    vtx_type const v = vertex.index;
    pid_type const home = partitioning->getAssignment(vertex);
    for (Edge const edge : graph->edgesOf(vertex)) {
      Vertex const u = graph->destinationOf(edge);
      pid_type const other = partitioning->getAssignment(u);
      if (other == home) {
        pair.internal += graph->weightOf(edge);
      } else {
        pair.external += graph->weightOf(edge);
      }
    }

    connectivity[v] = pair;
  }

  return TwoWayConnectivity(std::move(connectivity));
}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


TwoWayConnectivity::TwoWayConnectivity(
    sl::Array<vertex_struct> connectivity) :
  m_border(connectivity.size()),
  m_connectivity(std::move(connectivity))
{
  // fill in border
  for (vtx_type v = 0; v < m_connectivity.size(); ++v) {
    if (shouldBeInBorder(m_connectivity[v])) {
      m_border.add(v);
    }
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


bool TwoWayConnectivity::verify(
    Graph const * const graph,
    Partitioning const * const part) const
{
  bool good = true;
  // rebuild one and compare
  TwoWayConnectivity baseLine = \
      TwoWayConnectivity::fromPartitioning(graph, part);

  // verify border
  if (baseLine.m_border.size() != m_border.size()) {
    DEBUG_MESSAGE(std::string("Incorrect border size: ") + \
        std::to_string(m_border.size()) + std::string(" vs. ") + \
        std::to_string(baseLine.m_border.size()));
  }
  for (vtx_type const & v : m_border) {
    if (!baseLine.m_border.has(v)) {
      DEBUG_MESSAGE(getVertexDegreeString(v) + \
          std::string(" is in border, but not should be."));
      good = false; 
    }
  }
  for (vtx_type const & v : baseLine.m_border) {
    if (!m_border.has(v)) {
      DEBUG_MESSAGE(baseLine.getVertexDegreeString(v) + \
          std::string(" is not in border, but should be."));
      good = false; 
    }
  }

  // verify connectivity
  for (Vertex const & vertex : graph->vertices()) {
    vtx_type const v = vertex.index;
    if (m_connectivity[v].external != baseLine.m_connectivity[v].external || \
        m_connectivity[v].internal != baseLine.m_connectivity[v].internal) {
      DEBUG_MESSAGE(std::string("Incorrect info for ") + \
          getVertexDegreeString(v) + std::string(" vs. ") + \
          baseLine.getVertexDegreeString(v));
      good = false; 
    }
  }

  return good;
}
  
}
