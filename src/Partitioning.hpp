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
#include "ConstantGraph.hpp"


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
     * @param graph The graph that this is a partitioning of.
     */
    Partitioning(
        pid_type numParts,
        ConstantGraph const * graph);


    /**
    * @brief Move constructor.
    *
    * @param lhs The partitioning to move.
    */
    Partitioning(
        Partitioning && lhs) noexcept;


    /**
    * @brief Calculate the number of vertices per partition.
    *
    * @return The vector containing the number of vertices per partition.
    */
    std::vector<vtx_type> calcVertexCounts() const;


    /**
    * @brief Get the maximum imbalance as a fraction. That is, if a partition
    * is 5% overweight, this function will return 0.05.
    *
    * @param fractions The target weight fraction for each partition.
    *
    * @return The maximum imbalance.
    */
    double calcMaxImbalance(
        double const * const fractions) const;


    /**
    * @brief Parse a vector and alter this partitioning to match its
    * assignment.
    *
    * @param partitionAssignment The vertex assignment to partitions.
    */
    void input(
        pid_type const * partitionAssignment);


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
    * @brief Assign all vertices to a single partition. This function may be
    * called regardless of the current state of the partitioning.
    *
    * @param partition The partition to assign all vertices to.
    */
    void assignAll(
        pid_type partition);


    /**
    * @brief Set the cut edge weight.
    *
    * @param weight The cut edge weight.
    */
    inline void setCutEdgeWeight(
        wgt_type const weight) noexcept
    {
      m_cutEdgeWeight = weight;
    }


    /**
    * @brief Modify the cut edge weight.
    *
    * @param weightDelta The cut edge weight delta.
    */
    inline void addCutEdgeWeight(
        wgt_type const weightDelta) noexcept
    {
      m_cutEdgeWeight += weightDelta;
    }


    /**
     * @brief Get the number of partitions.
     *
     * @return The number of partitions. 
     */
    inline pid_type getNumPartitions() const noexcept
    {
      return static_cast<pid_type>(m_partitions.size());
    }


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
     * @param partition The partition to move the vertex to.
     */
    inline void move(
        vtx_type const vertex,
        pid_type const partition) noexcept
    {
      ASSERT_LESS(vertex, m_assignment.size());
      ASSERT_LESS(partition, m_partitions.size());
      ASSERT_NOTEQUAL(getAssignment(vertex), NULL_PID);

      wgt_type const weight = m_graph->getVertexWeight(vertex);

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
        vtx_type const vertex) noexcept
    {
      ASSERT_LESS(vertex, m_assignment.size());

      pid_type const current = getAssignment(vertex);

      ASSERT_NOTEQUAL(current, NULL_PID);

      m_partitions[current].weight -= m_graph->getVertexWeight(vertex);
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


    /**
    * @brief Get the weight the given partition.
    *
    * @param partition The partition id.
    *
    * @return The weight of the partition.
    */
    inline pid_type getWeight(
        pid_type const partition) const noexcept
    {
      ASSERT_LESS(partition, m_partitions.size());
      return m_partitions[partition].weight;
    }


  private:
    wgt_type m_cutEdgeWeight;

    std::vector<partition_struct> m_partitions;
    std::vector<pid_type> m_assignment;

    ConstantGraph const * m_graph;

    // disable copying
    Partitioning(
        Partitioning const & lhs);
    Partitioning & operator=(
        Partitioning const & lhs);

};

}


#endif
