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
#include "graph/ConstantGraph.hpp"
#include "Partition.hpp"
#include "solidutils/Debug.hpp"
#include "solidutils/Array.hpp"


namespace dolos
{

// TODO: This should be split into two classes -- a parittion builder which
// allows assignment, and then a partitioning which only allows movement
class Partitioning
{
  public:
    class Iterator
    {
      public:
        Iterator(
            vtx_type const index,
            wgt_type const * const partitionWeight) noexcept :
          m_index(index),
          m_partitionWeight(partitionWeight)
        {
          // do nothing
        }

        inline Partition operator*() const
        {
          return Partition(m_index, m_partitionWeight[m_index]);
        }

        inline Iterator & operator++()
        {
          ++m_index;
          return *this;
        }

        inline bool operator==(
            Iterator const & other) const
        {
          return m_index == other.m_index;
        }

        inline bool operator!=(
            Iterator const & other) const
        {
          return m_index != other.m_index;
        }

      private:
        adj_type m_index;
        wgt_type const * const m_partitionWeight;
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
    * @brief Create a new partitioning from an existing partition vector.
    *
    * @param numParts The number of parittions.
    * @param graph The graph.
    * @param partitionLabels The vector of partition labels (will be moved).
    */
    Partitioning(
        pid_type numParts,
        ConstantGraph const * graph,
        sl::Array<pid_type> * partitionLabels);


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
    * @brief Recalculate the cut edgeweight.
    */
    void recalcCutEdgeWeight();


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
    * @brief Set all vertices as unassigned.
    */
    void unassignAll();


    /**
    * @brief Get the partition with the given index.
    *
    * @param part The partition index.
    *
    * @return The partition.
    */
    inline Partition operator[](
        pid_type const part) const noexcept
    {
      return Partition(part, m_partitionWeight[part]);
    }


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
    * @brief Get the current weight of cut edges.
    *
    * @return The weight.
    */
    inline wgt_type getCutEdgeWeight() const noexcept
    {
      return m_cutEdgeWeight;
    }


    /**
     * @brief Get the number of partitions.
     *
     * @return The number of partitions. 
     */
    inline pid_type numPartitions() const noexcept
    {
      return static_cast<pid_type>(m_partitionWeight.size());
    }


    /**
     * @brief Assign a vertex to a parition. The vertex must not be already
     * assigned.
     *
     * @param vertex The vertex.
     * @param partition The partition to assign it to.
     */
    inline void assign(
        vtx_type const vertex,
        pid_type const partition) noexcept
    {
      ASSERT_LESS(vertex, m_assignment.size());
      ASSERT_LESS(partition, m_partitionWeight.size());
      ASSERT_EQUAL(getAssignment(vertex), NULL_PID);

      wgt_type const weight = m_graph->getVertexWeight(vertex);

      m_partitionWeight[partition] += weight;
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
      ASSERT_LESS(partition, m_partitionWeight.size());
      ASSERT_NOTEQUAL(getAssignment(vertex), NULL_PID);
      ASSERT_NOTEQUAL(getAssignment(vertex), partition);

      wgt_type const weight = m_graph->getVertexWeight(vertex);

      // remove from previous partition
      pid_type const current = getAssignment(vertex);
      m_partitionWeight[current] -= weight;

      // add to new partition
      m_partitionWeight[partition] += weight;
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

      m_partitionWeight[current] -= m_graph->getVertexWeight(vertex);
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
    inline wgt_type getWeight(
        pid_type const partition) const noexcept
    {
      ASSERT_LESS(partition, m_partitionWeight.size());
      return m_partitionWeight[partition];
    }


    /**
    * @brief Get the fraction of weight made up by the given partition.
    *
    * @param partition The partition.
    *
    * @return The fraction of weight.
    */
    inline double getFraction(
        pid_type const partition) const noexcept
    {
      ASSERT_LESS(partition, m_partitionWeight.size());
      return static_cast<double>(m_partitionWeight[partition]) / \
          static_cast<double>(m_graph->getTotalVertexWeight());
    }


    /**
    * @brief Get the begining iterator to the partitions.
    *
    * @return The iterator.
    */
    inline Iterator begin() const noexcept
    {
      return Iterator(0, m_partitionWeight.data());
    }


    /**
    * @brief Get the ending iterator to the partitions.
    *
    * @return The iterator.
    */
    inline Iterator end() const noexcept
    {
      return Iterator(m_partitionWeight.size(), m_partitionWeight.data());
    }


  private:
    wgt_type m_cutEdgeWeight;

    sl::Array<wgt_type> m_partitionWeight;
    sl::Array<pid_type> m_assignment;

    ConstantGraph const * m_graph;

    // disable copying
    Partitioning(
        Partitioning const & lhs);
    Partitioning & operator=(
        Partitioning const & lhs);

};

}


#endif