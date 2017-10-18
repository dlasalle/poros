/**
 * @fileMappedGraphWrapper.cpp
 * @brief Implementation of theMappedGraphWrapper class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-17
 */


#include "MappedGraph.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

MappedGraph::MappedGraph(
    ConstantGraph const * graph) :
  m_graph(graph)
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

ConstantGraph const *MappedGraphWrapper::getGraph() const
{
  return m_graph;
}


voidMappedGraphWrapper::mapPartitioning(
    Partitioning const * const subPart,
    Partitioning * const superPart,
    pid_type const offset) const
{
  for (Vertex const & vertex : getGraph()->getVertices()) {
    vtx_type const sub = vertex.getIndex();
    pid_type const assignment = subPart->getAssignment(sub);
    superPart->move(sub, assignment + offset);
  }

}

}
