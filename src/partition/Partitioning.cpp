/**
* @file Partitioning.cpp
* @brief Implementation of the partitioning class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-04
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


#include "Partitioning.hpp"


namespace poros
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{

template<bool HAS_VERTEX_WEIGHT>
void sumPartitionWeight(
    Graph const * const graph,
    pid_type const * const assignment,
    wgt_type * const partWeight)
{
   for (Vertex const & vertex : graph->vertices()) {
    vtx_type const v = vertex.index;
    pid_type const part = assignment[v];
    wgt_type const wgt = graph->weightOf<HAS_VERTEX_WEIGHT>(vertex);
    partWeight[part] += wgt;
  }
}

template<bool HAS_EDGE_WEIGHT>
wgt_type sumCutEdgeWeight(
    Graph const * const graph,
    pid_type const * const assignment)
{
  wgt_type twoWayCutEdgeWeight = 0;
  for (Vertex const vertex : graph->vertices()) {
    vtx_type const v = vertex.index;

    pid_type const home = assignment[v];
    for (Edge const edge : graph->edgesOf(vertex)) {
      Vertex const u = graph->destinationOf(edge);
      pid_type const other = assignment[u.index];
      if (other != home) {
        twoWayCutEdgeWeight += graph->weightOf<HAS_EDGE_WEIGHT>(edge);
      }
    }
  }

  return twoWayCutEdgeWeight / 2;
}

}

/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

Partitioning::Partitioning(
    pid_type const numParts,
    Graph const * const graph) :
  m_cutEdgeWeight(0),
  m_partitionWeight(numParts, 0),
  m_assignment(graph->numVertices(), NULL_PID),
  m_graph(graph)
{
  ASSERT_GREATER(numParts, 0);
}


Partitioning::Partitioning(
    pid_type const numParts,
    Graph const * const graph,
    sl::Array<pid_type> partitionLabels) :
  m_cutEdgeWeight(0),
  m_partitionWeight(numParts, 0),
  m_assignment(std::move(partitionLabels)),
  m_graph(graph)
{
  ASSERT_GREATER(numParts, 0);

  // calculate partition weights
  if (graph->hasUnitVertexWeight()) {
    sumPartitionWeight<false>(m_graph, m_assignment.data(), m_partitionWeight.data());
  } else {
    sumPartitionWeight<true>(m_graph, m_assignment.data(), m_partitionWeight.data());
  }

  if (m_graph->hasUnitEdgeWeight()) {
    m_cutEdgeWeight = sumCutEdgeWeight<false>(m_graph, m_assignment.data());
  } else {
    m_cutEdgeWeight = sumCutEdgeWeight<true>(m_graph, m_assignment.data());
  }
}


// use default generated -- must be done explicitly since we disabled copying
Partitioning::Partitioning(
    Partitioning && lhs) noexcept = default;

// use default generated -- must be done explicitly since we disabled copying
Partitioning& Partitioning::operator=(
    Partitioning && lhs) = default;



/******************************************************************************
* PUBLIC FUNCTIONS ************************************************************
******************************************************************************/


std::vector<vtx_type> Partitioning::calcVertexCounts() const
{
  std::vector<vtx_type> vertexCounts(numPartitions(), 0);
  for (pid_type const & part : m_assignment) {
    ++vertexCounts[part];
  }

  return vertexCounts;
}


void Partitioning::recalcCutEdgeWeight()
{
  if (m_graph->hasUnitEdgeWeight()) {
    m_cutEdgeWeight = sumCutEdgeWeight<false>(m_graph, m_assignment.data());
  } else {
    m_cutEdgeWeight = sumCutEdgeWeight<true>(m_graph, m_assignment.data());
  }
}


void Partitioning::assignAll(
    pid_type const partition)
{
  ASSERT_LESS(partition, numPartitions());

  m_cutEdgeWeight = 0;

  // move all vertices
  for (pid_type & where : m_assignment) {
    where = partition;
  }

  // set weights to zero
  for (wgt_type & partWeight : m_partitionWeight) {
    partWeight = 0;
  }

  // fix the one odd partition
  m_partitionWeight[partition] = m_graph->getTotalVertexWeight();
}


void Partitioning::unassignAll()
{
  for (pid_type & where : m_assignment) {
    where = NULL_PID;
  }

  // set weights to zero
  for (wgt_type & partWeight : m_partitionWeight) {
    partWeight = 0;
  }
}


void Partitioning::output(
    wgt_type * const totalCutEdgeWeight,
    pid_type * const partitionAssignment) const noexcept
{
  *totalCutEdgeWeight = m_cutEdgeWeight;

  vtx_type const numVertices = static_cast<vtx_type>(m_assignment.size());
  for (vtx_type v = 0; v < numVertices; ++v) {
    partitionAssignment[v] = m_assignment[v];
  }
}


}
