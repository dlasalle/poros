/**
* @file Subgraph.cpp
* @brief Implementation of the Subgraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-10
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


#include "Subgraph.hpp"
#include "solidutils/VectorMath.hpp"


namespace poros
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

