/**
* @file Subgraph.cpp
* @brief Implementation of the Subgraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
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
    ConstantGraph * const graph,
    sl::Array<vtx_type> * const superMap) :
  m_superMap(std::move(*superMap)),
  m_graph(std::move(*graph))
{
  // do nothing
}


Subgraph::Subgraph(
    ConstantGraph * const graph) :
  m_superMap(graph->numVertices()),
  m_graph(std::move(*graph))
{
  sl::VectorMath::increment(m_superMap.data(), m_superMap.size());
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


ConstantGraph const * Subgraph::getGraph() const
{
  return &m_graph;
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
  for (Vertex const & vertex : getGraph()->vertices()) {
    vtx_type const sub = vertex.index();
    pid_type const assignment = subPart->getAssignment(sub);
    vtx_type const super = getSuperMap(sub);
    partitionLabels[super] = assignment + offset;
  }
}

}

