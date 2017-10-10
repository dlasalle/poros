/**
* @file Partitioning.cpp
* @brief Implementation of the partitioning class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-04
*/


#include "Partitioning.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

Partitioning::Partitioning(
    pid_type const numParts,
    vtx_type const numVertices) :
  m_cutEdgeWeight(0),
  m_partitions(numParts, {0}),
  m_assignment(numVertices, NULL_PID)
{
  ASSERT_GREATER(numParts, 0);
  ASSERT_GREATER(numVertices, 0);
}


// use default generated -- must be done explicitly since we disabled copying
Partitioning::Partitioning(
    Partitioning && lhs) noexcept = default;


/******************************************************************************
* PUBLIC FUNCTIONS ************************************************************
******************************************************************************/

void Partitioning::assignAll(
    pid_type const partition,
    wgt_type const totalVertexWeight)
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
  m_partitions[partition].weight = totalVertexWeight;
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
