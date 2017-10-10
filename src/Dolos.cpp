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
#include "ConstantGraph.hpp"
#include "Partitioning.hpp"
#include "PartitionParameters.hpp"
#include "RandomBisector.hpp"
#include "RecursiveBisectionPartitioner.hpp"

using namespace dolos;

extern "C" {


int DOLOS_PartGraphRecursive(
    vtx_type const numVertices,
    adj_type const * const edgePrefix,
    vtx_type const * const edgeList,
    wgt_type const * const vertexWeights,
    wgt_type const * const edgeWeights,
    pid_type const numPartitions,
    dolos_options_struct const * const options,
    wgt_type * const totalCutEdgeWeight,
    pid_type * const partitionAssignment)
{
  // create a parameters object

  // assemble a new graph
  ConstantGraph baseGraph(numVertices, edgePrefix[numVertices], edgePrefix, \
      edgeList, vertexWeights, edgeWeights);


  // setup paramters for the partition
  PartitionParameters params(numPartitions);

  // partition the graph
  RandomBisector bisector;
  RecursiveBisectionPartitioner partitioner(&bisector);
  Partitioning part = partitioner.execute(&params, &baseGraph);

  // output data
  part.output(totalCutEdgeWeight, partitionAssignment);

  return 1;
}

}
