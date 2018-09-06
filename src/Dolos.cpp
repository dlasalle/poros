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
#include "partition/BFSBisector.hpp"
#include "partition/MultiBisector.hpp"
#include "partition/FMRefiner.hpp"
#include "aggregation/HeavyEdgeMatchingAggregator.hpp"
#include "partition/MultilevelBisector.hpp"
#include "partition/RecursiveBisectionPartitioner.hpp"
#include "util/SimpleRandomEngine.hpp"
#include "DolosParameters.hpp"


using namespace dolos;


/******************************************************************************
* PUBLIC FUNCTIONS ************************************************************
******************************************************************************/

dolos_options_struct DOLOS_defaultOptions()
{
  dolos_options_struct opts{
    0.03,
    nullptr,
    0,
    8,
    SORTED_HEAVY_EDGE_MATCHING
  };

  return opts;
}

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
  DolosParameters globalParams(options);

  // create a parameters object
  RandomEngineHandle randEngine = globalParams.randomEngine();

  // assemble a new graph
  ConstantGraph baseGraph(numVertices, edgePrefix[numVertices], edgePrefix, \
      edgeList, vertexWeights, edgeWeights);

  // setup paramters for the partition
  PartitionParameters params(numPartitions);

  // partition the graph
  std::unique_ptr<IAggregator> rm(new HeavyEdgeMatchingAggregator(randEngine));
  std::unique_ptr<IBisector> rb(new BFSBisector(randEngine));
  std::unique_ptr<IBisector> mb(new MultiBisector(8, rb.get()));
  std::unique_ptr<ITwoWayRefiner> fm(new FMRefiner(8));

  MultilevelBisector ml(std::move(rm), std::move(mb), std::move(fm));

  RecursiveBisectionPartitioner partitioner(&ml);

  TargetPartitioning target(params.numPartitions(), \
      baseGraph.getTotalVertexWeight(), params.getImbalanceTolerance(), \
      params.getTargetPartitionFractions());

  Partitioning part = partitioner.execute(&target, &baseGraph);

  // output data
  part.output(totalCutEdgeWeight, partitionAssignment);

  return 1;
}
