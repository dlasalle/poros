/**
 * @file dolos.h
 * @brief Top level header file for Dolos (a modern implementation of Metis). 
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Partition a graph using recursive bisection.
 *
 * @param numVertices The number of vertices in the graph.
 * @param edgePrefix The prefixsum of the edge list (xadj or rowptr).
 * @param edgeList The list of edge endpoints (adjncy or rowind).
 * @param vertexWeights The list of vertex weights.
 * @param edgeWeights The weight associated with each edge.
 * @param numPartitions The number of partitions to create.
 * @param targetPartitionFractions The fraction of weight for each partition.
 * If this is nullptr, then each partition will be of equal weight.
 * @param imbalanceTolerance The level of imbalance tolerance to accept.
 * @param totalCutEdgeWeight The total weight of cut edges (output).
 * @param partitionAssignment The partition assignment of each vertex.
 *
 * @return 1 on success, 0 if an error occurs.
 */
int DOLOS_PartGraphRecursive(
    dolos_vtx_type numVertices,
    dolos_adj_type edgePrefix,
    dolos_vtx_type edgeList,
    dolos_wgt_type vertexWeights,
    dolos_wgt_type edgeWeights,
    dolos_pid_type numPartitions,
    double targetPartitionFractions,
    double imbalanceTolerance,
    dolos_wgt_type * totalCutEdgeWeight,
    dolos_pid_type * partitionAssignment);


#ifdef __cplusplus
}
#endif
