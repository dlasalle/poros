/**
 * @file Partitioning.hpp
 * @brief The Partitioning class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#ifndef DOLOS_SRC_PARTITIONING_HPP
#define DOLOS_SRC_PARTITIONING_HPP


#include <vector>
#include "Base.hpp"
#include "Debug.hpp"


namespace dolos
{

class Partitioning
{
  public:
    struct partition_struct {
      wgt_type weight;
    };

    /**
     * @brief Create a new partitioning with the given number of partitions.
     *
     * @param numParts The number of partitions.
     * @param numVertices The number of vertices.
     */
    Partitioning(
        pid_type numParts,
        vtx_type numVertices);

    /**
     * @brief Get the number of partitions.
     *
     * @return The number of partitions. 
     */
    pid_type getNumPartitions() const noexcept;

    /**
     * @brief Get the heaviest parition.
     *
     * @return The heaviest (most unbalanced parititon).
     */
    partition_struct const * getHeaviestPartition() const;


    /**
     * @brief Output the partition to a given memory location.
     *
     * @param totalCutEdgeWeight The location to write the total cut
     * edgeweight. 
     * @param partitionAssignment The location to write vertex assignments to.
     */
    void output(
        wgt_type * totalCutEdgeWeight,
        pid_type * partitionAssignment) const noexcept;


    /**
     * @brief Assign a vertex to a parition. The vertex must not be already
     * assigned.
     *
     * @param vertex The vertex.
     * @param weight The weight of the vertex.
     * @param partition The partition to assign it to.
     */
    inline void assign(
        vtx_type const vertex,
        wgt_type const weight,
        pid_type const partition) noexcept
    {
      ASSERT_LESS(vertex, m_assignment.size());
      ASSERT_LESS(partition, m_partitions.size());
      ASSERT_EQUAL(getAssignment(vertex), NULL_PID);

      m_partitions[partition].weight += weight;
      m_assignment[vertex] = partition;
    }


    /**
     * @brief Move a vertex between partitions.
     *
     * @param vertex The vertex to move.
     * @param weight The weight of the vertex.
     * @param partition The partition to move the vertex to.
     */
    inline void move(
        vtx_type const vertex,
        wgt_type const weight,
        pid_type const partition) noexcept
    {
      ASSERT_LESS(vertex, m_assignment.size());
      ASSERT_LESS(partition, m_partitions.size());
      ASSERT_NOTEQUAL(getAssignment(vertex), NULL_PID);

      // remove from previous partition
      pid_type const current = getAssignment(vertex);
      m_partitions[current].weight -= weight;

      // add to new partition
      m_partitions[partition].weight += weight;
      m_assignment[vertex] = partition;
    }


    /**
     * @brief Unassign a vertex. The vertex must be already assigned.
     *
     * @param vertex The vertex to unassign.
     * @param weight The weight of the vertex.
     */
    inline void unassign(
        vtx_type const vertex,
        wgt_type const weight) noexcept
    {
      ASSERT_LESS(vertex, m_assignment.size());

      pid_type const current = getAssignment(vertex);

      ASSERT_NOTEQUAL(current, NULL_PID);

      m_partitions[current].weight -= weight;
      m_assignment[vertex] = NULL_PID;
    }


    /**
     * @brief Get the assignment of the vertex.
     *
     * @param vertex The vertex.
     *
     * @return The assignment.
     */
    inline pid_type getAssignment(
        vtx_type const vertex) const noexcept
    {
      ASSERT_LESS(vertex, m_assignment.size());

      return m_assignment[vertex];
    }

    /**
     * @brief Check if a vertex has been assigned yet.
     *
     * @param vertex The vertex to check.
     *
     * @return True if the vertex has been assigned to a partition.
     */
    inline bool isAssigned(
        vtx_type const vertex) const noexcept
    {
      return getAssignment(vertex) != NULL_PID;
    }


  private:
    std::vector<partition_struct> m_partitions;
    std::vector<pid_type> m_assignment;

};

}


#endif
