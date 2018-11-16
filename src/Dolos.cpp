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
#include "DolosParameters.hpp"
#include "graph/Graph.hpp"
#include "partition/Partitioning.hpp"
#include "partition/PartitionParameters.hpp"
#include "partition/BisectorFactory.hpp"
#include "partition/MultiBisector.hpp"
#include "partition/TwoWayRefinerFactory.hpp"
#include "aggregation/AggregatorFactory.hpp"
#include "partition/MultilevelBisector.hpp"
#include "partition/RecursiveBisectionPartitioner.hpp"
#include "util/RandomEngineHandle.hpp"
#include "util/TimeKeeper.hpp"

#include "solidutils/Timer.hpp"

#include <iostream>


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
    SORTED_HEAVY_EDGE_MATCHING,
    false
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
  if (options == nullptr) {
    // options must not be null
    return 0;
  }

  sl::Timer totalTimer;
  totalTimer.start();

  std::shared_ptr<TimeKeeper> timeKeeper(new TimeKeeper);

  DolosParameters globalParams(*options);

  // create a parameters object
  RandomEngineHandle randEngine = globalParams.randomEngine();

  // assemble a new graph
  Graph baseGraph(numVertices, edgePrefix[numVertices], edgePrefix, \
      edgeList, vertexWeights, edgeWeights);

  // setup paramters for the partition
  PartitionParameters params(numPartitions);

  // partition the graph
  std::unique_ptr<IAggregator> agg = AggregatorFactory::make(
      globalParams.aggregationScheme(), randEngine, timeKeeper);

  std::unique_ptr<IBisector> bisector = \
      BisectorFactory::make(BFS_BISECTION, randEngine, 8, timeKeeper);
  std::unique_ptr<ITwoWayRefiner> refiner = \
      TwoWayRefinerFactory::make(FM_TWOWAY_REFINEMENT, timeKeeper);

  MultilevelBisector ml(std::move(agg), std::move(bisector), \
      std::move(refiner), timeKeeper);

  RecursiveBisectionPartitioner partitioner(&ml);

  TargetPartitioning target(params.numPartitions(), \
      baseGraph.getTotalVertexWeight(), params.getImbalanceTolerance(), \
      params.getTargetPartitionFractions());

  Partitioning part = partitioner.execute(&target, &baseGraph);

  // output data
  part.output(totalCutEdgeWeight, partitionAssignment);

  totalTimer.stop();
  timeKeeper->reportTime(TimeKeeper::TOTAL, totalTimer.poll());

  if (options->outputTimes) {
    for (std::pair<std::string, double> const & pair : timeKeeper->times()) {
      std::cout << pair.first << ": " << pair.second << std::endl;
    }
  }

  return 1;
}
