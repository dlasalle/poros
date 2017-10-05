/**
 * @file Dolos.cpp
 * @brief Top level functions. 
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#include "dolos.h"
#include "Base.hpp"
#include "Parameters.hpp"

using namespace dolos;

extern "C" {


int DOLOS_PartGraphRecursive(
    vtx_type const numVertices,
    adj_type const * const edgePrefix,
    vtx_type const * const edgeList,
    wgt_type const * const vertexWeights,
    wgt_type const * const edgeWeights,
    pid_type const numPartitions,
    double const * const targetPartitionFractions,
    double const imbalanceTolerance,
    wgt_type * const totalCutEdgeWeight,
    pid_type * const partitionAssignment)
{
  // create a parameters object
  Parameters params(options);

  // assemble a new graph
  Graph baseGraph(numVertices, edgePrefix[numVertices], edgePrefix, edgeList, \
      vertexWeights, edgeWeights);

  // partition the graph
  RecursiveBisector partitioner(params);
  Partitioning part = partitioner.execute(base);

  // output data
  part.output(totalCutEdgeWeight, partitionAssignment);

  return 1;
}

}
