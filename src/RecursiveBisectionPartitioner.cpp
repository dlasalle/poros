/**
* @file RecursiveBisectionPartitioner.cpp
* @brief Implementation of the RecursiveBisectionPartitioner.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2017-10-10
*/


#include "RecursiveBisectionPartitioner.hpp"

#include <cmath>
#include "MappedGraphWrapper.hpp"
#include "SubgraphExtractor.hpp"
#include "solidutils/VectorMath.hpp"


namespace dolos
{


/******************************************************************************
* PRIVATE METHODS *************************************************************
******************************************************************************/

void RecursiveBisectionPartitioner::recurse(
    pid_type * const partitionLabels,
    PartitionParameters const * const params,
    IMappedGraph const * mappedGraph,
    pid_type const offset) const
{
  ConstantGraph const * const graph = mappedGraph->getGraph();
  
  // build parameters for bisection
  BisectionParameters bisectParams;

  pid_type const numParts = params->getNumPartitions();

  // We don't want to use the k-way imbalance tolerance, as if one half of the
  // bisection is at maximum weight, then each partition with in that half must
  // also be at maximum weight (in the case of non-uniform vertex weights we
  // may find it impossible to balance). So instead, what we do is use
  // \eps / \log_2(k)
  double const tolerance = params->getImbalanceTolerance() / \
      std::log2(params->getNumPartitions());
  bisectParams.setImbalanceTolerance(tolerance);

  double const * const targetFractions = params->getTargetPartitionFractions();

  // calculate target fractions
  sl::Array<pid_type> numPartsPrefix(3);
  numPartsPrefix.set(0);

  std::vector<double> targetBisectionFractions(NUM_BISECTION_PARTS, 0);
  for (pid_type pid = 0; pid < numParts; ++pid) {
    // we must put a larger or equal number of partitions in the second half
    pid_type const half = static_cast<pid_type>(pid >= numParts/2);
    targetBisectionFractions[half] += targetFractions[pid];
    ++numPartsPrefix[half];
  }
  bisectParams.setTargetPartitionFractions(targetBisectionFractions.data());
  sl::VectorMath::prefixSumExclusive(numPartsPrefix.data(), \
      numPartsPrefix.size());

  // calculate the target weight for each side bisect
  Partitioning bisection = m_bisector->execute(&bisectParams, graph);

  // NOTE: this requires that for uneven number of parts, latter half has more
  ASSERT_GREATEREQUAL(numPartsPrefix[2]-numPartsPrefix[1], \
    numPartsPrefix[1]-numPartsPrefix[0]);
  mappedGraph->mapPartitioning(&bisection, partitionLabels, offset);

  if (numParts > 2) {
    // extract graph parts
    std::vector<Subgraph> parts = SubgraphExtractor::partitions(graph, \
        &bisection);
    ASSERT_EQUAL(parts.size(), NUM_BISECTION_PARTS);

    for (pid_type part = 0; part < parts.size(); ++part) {
      pid_type const numHalfParts = numPartsPrefix[part+1] - \
          numPartsPrefix[part];

      double const halfTargetFraction = targetBisectionFractions[part];
      double const weightFrac = \
          static_cast<double>(bisection.getWeight(part)) / \
          static_cast<double>(graph->getTotalVertexWeight()) ;

      double const ratio = (weightFrac / halfTargetFraction) - 1.0;

      if (numHalfParts > 1) {
        // recursively call execute
        PartitionParameters subParams(numHalfParts);

        std::vector<double> subTargetFractions(numHalfParts);
        for (pid_type pid = 0; pid < numHalfParts; ++pid) {
          pid_type const offsetPid = pid + numPartsPrefix[part];
          subTargetFractions[pid] = \
              targetFractions[offsetPid] / halfTargetFraction;
        }
        subParams.setImbalanceTolerance(params->getImbalanceTolerance() - \
            ratio);
        subParams.setTargetPartitionFractions(subTargetFractions.data());

        recurse(partitionLabels, &subParams, &(parts[part]), \
            offset+numPartsPrefix[part]);
      }
    }
  }
}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


RecursiveBisectionPartitioner::RecursiveBisectionPartitioner(
    IBisector const * const bisector) :
  m_bisector(bisector)
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


Partitioning RecursiveBisectionPartitioner::execute(
    PartitionParameters const * params,
    ConstantGraph const * graph) const
{
  sl::Array<pid_type> partitionLabels(graph->getNumVertices());

  MappedGraphWrapper mappedGraph(graph);
  recurse(partitionLabels.data(), params, &mappedGraph, 0);

  Partitioning part(params->getNumPartitions(), graph, &partitionLabels);
  part.recalcCutEdgeWeight();

  return part;
}

}
