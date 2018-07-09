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
#include "graph/ConstantGraph.hpp"
#include "partition/Partitioning.hpp"
#include "partition/PartitionParameters.hpp"
#include "partition/RandomBisector.hpp"
#include "partition/RecursiveBisectionPartitioner.hpp"
#include "util/SimpleRandomEngine.hpp"


using namespace dolos;


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
  SimpleRandomEngine randEngine;

  // assemble a new graph
  ConstantGraph baseGraph(numVertices, edgePrefix[numVertices], edgePrefix, \
      edgeList, vertexWeights, edgeWeights);


  // setup paramters for the partition
  PartitionParameters params(numPartitions);

  // partition the graph
  RandomBisector bisector(&randEngine);
  RecursiveBisectionPartitioner partitioner(&bisector);


  TargetPartitioning target(params.numPartitions(), \
      baseGraph.getTotalVertexWeight(), params.getImbalanceTolerance(), \
      params.getTargetPartitionFractions());

  Partitioning part = partitioner.execute(&target, &baseGraph);

  // output data
  part.output(totalCutEdgeWeight, partitionAssignment);

  return 1;
}
