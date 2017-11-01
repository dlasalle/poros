/**
* @file Partitioning.cpp
* @brief Implementation of the partitioning class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-04
*/


#include "Partitioning.hpp"

// delete me
#include <cstdio>

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

Partitioning::Partitioning(
    pid_type const numParts,
    ConstantGraph const * const graph) :
  m_cutEdgeWeight(0),
  m_partitions(numParts, {0}),
  m_assignment(graph->getNumVertices(), NULL_PID),
  m_graph(graph)
{
  ASSERT_GREATER(numParts, 0);
}


Partitioning::Partitioning(
    pid_type const numParts,
    sl::Array<pid_type> * const partitionLabels,
    ConstantGraph const * const graph) :
  m_cutEdgeWeight(0),
  m_partitions(numParts, {0}),
  m_assignment(std::move(*partitionLabels)),
  m_graph(graph)
{
  ASSERT_GREATER(numParts, 0);
}


// use default generated -- must be done explicitly since we disabled copying
Partitioning::Partitioning(
    Partitioning && lhs) noexcept = default;


/******************************************************************************
* PUBLIC FUNCTIONS ************************************************************
******************************************************************************/


std::vector<vtx_type> Partitioning::calcVertexCounts() const
{
  std::vector<vtx_type> vertexCounts(getNumPartitions(), 0);
  for (vtx_type const & part : m_assignment) {
    ++vertexCounts[part];
  }

  return vertexCounts;
}


void Partitioning::recalcCutEdgeWeight()
{
  double twoWayCutEdgeWeight = 0;
  for (Vertex const & vertex : m_graph->getVertices()) {
    vtx_type const v = vertex.getIndex();

    pid_type const home = m_assignment[v];
    for (Edge const & edge : vertex.getEdges()) {
      vtx_type const u = edge.getVertex();
      pid_type const other = m_assignment[u];
      if (other != home) {
        twoWayCutEdgeWeight += edge.getWeight();
      }
    }
  }

  m_cutEdgeWeight = twoWayCutEdgeWeight / 2;
}


void Partitioning::assignAll(
    pid_type const partition)
{
  ASSERT_LESS(partition, m_partitions.size());

  m_cutEdgeWeight = 0;

  // move all vertices
  for (pid_type & where : m_assignment) {
    where = partition;
  }

  // set weights to zero
  for (partition_struct & p : m_partitions) {
    p.weight = 0;
  }

  // fix the one odd partition
  m_partitions[partition].weight = m_graph->getTotalVertexWeight();
}


void Partitioning::unassignAll()
{
  for (pid_type & where : m_assignment) {
    where = NULL_PID;
  }

  for (partition_struct & p : m_partitions) {
    p.weight = 0;
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
