/**
 * @file dolos.h
 * @brief Top level header file for Dolos (a modern implementation of Metis). 
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */



#ifndef DOLOS_H
#define DOLOS_H


#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif


typedef uint32_t dolos_vtx_type;
typedef uint64_t dolos_adj_type;
typedef uint32_t dolos_wgt_type;
typedef uint32_t dolos_pid_type;


/**
 * @brief Aggregation types.
 */
typedef enum {
    RANDOM_MATCHING = 0,
    SORTED_HEAVY_EDGE_MATCHING = 1
} aggregator_type;


typedef struct {
  /**
   * @brief The fraction of imbalance to accept (i.e., 0.03 allows for one
   * partition to be 3% higher than its target).
   */
  double imbalanceTolerance;

  /**
   * @brief The fraction of weight for each partition.
   * If this is null, then each partition will be of equal weight, otherwise it
   * must be of length of the number of partitions and sum to 1.0.
   */
  double * targetPartitionFractions;

  /**
   * @brief The random seed to use for generating random numbers.
   */
  unsigned int randomSeed;

  /**
   * @brief The maximum number of refinement iterations to perform. A value of
   * -1 will result in there being no maximum (any other negative value will
   * result in an error). A value of 0 will prevent refinement from being
   * performed.
   */
  int refinementIterations;

  /**
   * @brief The type of aggregation to perform. Should be a member of the
   * `aggreagtor_type` enum.
   */
  int aggregationScheme;

} dolos_options_struct;


/**
 * @brief Generate the default options to execute Dolos with.
 *
 * @return The default options.
 */
dolos_options_struct DOLOS_defaultOptions(void);


/**
 * @brief Partition a graph using recursive bisection.
 *
 * @param numVertices The number of vertices in the graph.
 * @param edgePrefix The prefixsum of the edge list (xadj or rowptr).
 * @param edgeList The list of edge endpoints (adjncy or rowind).
 * @param vertexWeights The list of vertex weights (if null, every vertex will
 * be assigned a weight of 1).
 * @param edgeWeights The weight associated with each edge (if null, every
 * edge will be assigned a weight of 1).
 * @param numPartitions The number of partitions to create.
 * @param options The list of options to use. This may be null when the
 * defaults are desired.
 * @param totalCutEdgeWeight The total weight of cut edges (output).
 * @param partitionAssignment The partition assignment of each vertex.
 *
 * @return 1 on success, 0 if an error occurs.
 */
int DOLOS_PartGraphRecursive(
    dolos_vtx_type numVertices,
    dolos_adj_type const * edgePrefix,
    dolos_vtx_type const * edgeList,
    dolos_wgt_type const * vertexWeights,
    dolos_wgt_type const * edgeWeights,
    dolos_pid_type numPartitions,
    dolos_options_struct const * options,
    dolos_wgt_type * totalCutEdgeWeight,
    dolos_pid_type * partitionAssignment);



#ifdef __cplusplus
}
#endif

#endif
