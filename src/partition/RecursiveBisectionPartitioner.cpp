/**
* @file RecursiveBisectionPartitioner.cpp
* @brief Implementation of the RecursiveBisectionPartitioner.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2017-10-10
*/


#include "RecursiveBisectionPartitioner.hpp"

#include "graph/MappedGraphWrapper.hpp"
#include "graph/SubgraphExtractor.hpp"
#include "partition/TargetPartitioning.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "solidutils/VectorMath.hpp"

#include <cmath>

namespace dolos
{


/******************************************************************************
* PRIVATE METHODS *************************************************************
******************************************************************************/

void RecursiveBisectionPartitioner::recurse(
    pid_type * const partitionLabels,
    TargetPartitioning const * const target,
    IMappedGraph const * const mappedGraph,
    pid_type const offset)
{
  ConstantGraph const * const graph = mappedGraph->getGraph();
  
  pid_type const numParts = target->numPartitions();

  // We don't want to use the k-way imbalance tolerance, as if one half of the
  // bisection is at maximum weight, then each partition with in that half must
  // also be at maximum weight (in the case of non-uniform vertex weights we
  // may find it impossible to balance). So instead, what we do is use
  // \eps / \log_2(k)
  double const tolerance = target->getImbalanceTolerance() / \
      std::log2(target->numPartitions());

  double const * const targetFractions = target->getTargetFraction();

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

  // build parameters for bisection
  TargetPartitioning bisectTarget(2, graph->getTotalVertexWeight(), \
      tolerance, targetBisectionFractions.data());

  sl::VectorMath::prefixSumExclusive(numPartsPrefix.data(), \
      numPartsPrefix.size());

  // calculate the target weight for each side bisect
  Partitioning bisection = m_bisector->execute(&bisectTarget, graph);
  PartitioningAnalyzer analyzer(&bisection, &bisectTarget);

  DEBUG_MESSAGE(std::string("Made bisection of balance ") + \
      std::to_string(analyzer.calcMaxImbalance()) + std::string("/") + \
      std::to_string(bisectTarget.getImbalanceTolerance()) + \
      std::string(" (") + \
      std::to_string(bisection.getWeight(LEFT_PARTITION)) + \
      std::string(":") + \
      std::to_string(bisection.getWeight(RIGHT_PARTITION)) + std::string(")"));

  // NOTE: this requires that for uneven number of parts, latter half has more
  ASSERT_GREATEREQUAL(numPartsPrefix[2]-numPartsPrefix[1], \
      numPartsPrefix[1]-numPartsPrefix[0]);
  mappedGraph->mapPartitioning(&bisection, partitionLabels, offset);

  if (numParts > 2) {
    // extract graph parts
    Subgraph const * subgraphPtr;
    vtx_type const * superMap = nullptr;
    if ( (subgraphPtr = dynamic_cast<Subgraph const *>(mappedGraph)) ) {
      superMap = subgraphPtr->getSuperMap();
    }
    std::vector<Subgraph> parts = SubgraphExtractor::partitions(graph, \
        &bisection, superMap);

    ASSERT_EQUAL(parts.size(), NUM_BISECTION_PARTS);

    for (pid_type part = 0; part < parts.size(); ++part) {
      pid_type const numHalfParts = numPartsPrefix[part+1] - \
          numPartsPrefix[part];

      double const halfTargetFraction = targetBisectionFractions[part];

      double const ratio = analyzer.getImbalance(part);

      if (numHalfParts > 1) {
        // recursively call execute
        std::vector<double> subTargetFractions(numHalfParts);
        for (pid_type pid = 0; pid < numHalfParts; ++pid) {
          pid_type const offsetPid = pid + numPartsPrefix[part];
          subTargetFractions[pid] = \
              targetFractions[offsetPid] / halfTargetFraction;
        }
        TargetPartitioning subTarget(numHalfParts, \
            parts[part].getGraph()->getTotalVertexWeight(), \
            target->getImbalanceTolerance() - ratio, \
            subTargetFractions.data());

        recurse(partitionLabels, &subTarget, &(parts[part]), \
            offset+numPartsPrefix[part]);
      }
    }
  }
}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


RecursiveBisectionPartitioner::RecursiveBisectionPartitioner(
    IBisector * const bisector) :
  m_bisector(bisector)
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


Partitioning RecursiveBisectionPartitioner::execute(
    TargetPartitioning const * const target,
    ConstantGraph const * const graph)
{
  sl::Array<pid_type> partitionLabels(graph->numVertices());

  MappedGraphWrapper mappedGraph(graph);
  recurse(partitionLabels.data(), target, &mappedGraph, 0);

  Partitioning part(target->numPartitions(), graph, &partitionLabels);
  part.recalcCutEdgeWeight();

  return part;
}

}
