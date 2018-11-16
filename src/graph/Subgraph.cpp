/**
* @file Subgraph.cpp
* @brief Implementation of the Subgraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-10
*/


#include "Subgraph.hpp"
#include "solidutils/VectorMath.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


Subgraph::Subgraph(
    GraphHandle graph,
    sl::Array<vtx_type> superMap) :
  m_superMap(std::move(superMap)),
  m_graph(graph)
{
  // do nothing
}


Subgraph::Subgraph(
    GraphHandle graph) :
  m_superMap(graph->numVertices()),
  m_graph(graph)
{
  sl::VectorMath::increment(m_superMap.data(), m_superMap.size());
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


Graph const * Subgraph::getGraph() const
{
  return m_graph.get();
}


vtx_type const * Subgraph::getSuperMap() const
{
  return m_superMap.data();
}


void Subgraph::mapPartitioning(
    Partitioning const * const subPart,
    pid_type * const partitionLabels,
    pid_type const offset) const
{
  // translate partitioning
  for (Vertex const vertex : m_graph->vertices()) {
    pid_type const assignment = subPart->getAssignment(vertex);
    vtx_type const super = m_superMap[vertex.index];
    partitionLabels[super] = assignment + offset;
  }
}

}

