/**
 * @file Poros.cpp
 * @brief Top level functions.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018
 * @version 1
 * @date 2017-10-04
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */


#include "poros.h"

#include "Base.hpp"
#include "PorosParameters.hpp"
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


using namespace poros;


/******************************************************************************
* PUBLIC FUNCTIONS ************************************************************
******************************************************************************/

poros_options_struct POROS_defaultOptions()
{
  poros_options_struct opts{
    0.03,
    nullptr,
    0,
    8,
    SORTED_HEAVY_EDGE_MATCHING,
    false
  };

  return opts;
}

int POROS_PartGraphRecursive(
    vtx_type const numVertices,
    adj_type const * const edgePrefix,
    vtx_type const * const edgeList,
    wgt_type const * vertexWeights,
    wgt_type const * edgeWeights,
    pid_type const numPartitions,
    poros_options_struct const * const options,
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

  PorosParameters globalParams(*options);

  // create a parameters object
  RandomEngineHandle randEngine = globalParams.randomEngine();

  // allocate unit edge weights and vertex weights of needed
  sl::Array<wgt_type> unitVwgts;
  if (vertexWeights == nullptr) {
    unitVwgts = sl::Array<wgt_type>(numVertices, 1);
    vertexWeights = unitVwgts.data();
  }
  sl::Array<wgt_type> unitEwgts;
  if (edgeWeights == nullptr) {
    unitEwgts = sl::Array<wgt_type>(edgePrefix[numVertices], 1);
    edgeWeights = unitEwgts.data();
  }

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
