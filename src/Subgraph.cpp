/**
* @file Subgraph.cpp
* @brief Implementation of the Subgraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/


#include "Subgraph.hpp"



namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


Subgraph::Subgraph(
    ConstantGraph * graph,
    Array<vtx_type> * superMap) :
  m_superMap(std::move(*superMap)),
  m_graph(std::move(*graph))
{
  // do nothing
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
    Partitioning * const superPart,
    pid_type const offset) const
{
  // translate partitioning
  for (Vertex const & vertex : getGraph()->getVertices()) {
    vtx_type const sub = vertex.getIndex();
    pid_type const assignment = subPart->getAssignment(sub);
    vtx_type const super = getSuperMap(sub);
    superPart->move(super, assignment + offset);
  }
}

}

