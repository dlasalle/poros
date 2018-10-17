/**
 * @fileMappedGraphWrapper.cpp
 * @brief Implementation of theMappedGraphWrapper class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018
 * @version 1
 * @date 2017-10-17
 */


#include "MappedGraphWrapper.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

MappedGraphWrapper::MappedGraphWrapper(
    ConstantGraph const * graph) :
  m_graph(graph)
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

ConstantGraph const * MappedGraphWrapper::getGraph() const
{
  return m_graph;
}


void MappedGraphWrapper::mapPartitioning(
    Partitioning const * const subPart,
    pid_type * const partitionLabels,
    pid_type const offset) const
{
  for (Vertex const vertex : getGraph()->vertices()) {
    pid_type const assignment = subPart->getAssignment(vertex);
    partitionLabels[vertex.index] = assignment + offset;
  }
}

}
