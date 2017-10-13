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
#include "SubgraphExtractor.hpp"
#include "PartitioningAnalyzer.hpp"



namespace dolos
{


RecursiveBisectionPartitioner::RecursiveBisectionPartitioner(
    IBisector const * const bisector) :
  m_bisector(bisector)
{
  // do nothing
}


Partitioning RecursiveBisectionPartitioner::execute(
    PartitionParameters const * params,
    ConstantGraph const * graph) const
{
  Partitioning partitioning(params->getNumPartitions(), \
      graph->getNumVertices());

  // build parameters for bisection
  BisectionParameters bisectParams;

  // We don't want to use the k-way imbalance tolerance, as if one half of the
  // bisection is at maximum weight, then each partition with in that half must
  // also be at maximum weight (in the case of non-uniform vertex weights we
  // may find it impossible to balance). So instead, what we do is use
  // \eps / \log_2(k)
  double const tolerance = params->getImbalanceTolerance() / \
      std::log2(params->getNumPartitions());
  bisectParams.setImbalanceTolerance(tolerance);

  // calculate the target weight for each side
  std::vector<pid_type> numHalfParts(2);
  numHalfParts[0] = params->getNumPartitions() / 2;
  numHalfParts[1] = params->getNumPartitions() - numHalfParts[0];

  // bisect
  Partitioning bisection = m_bisector->execute(&bisectParams, graph);

  // extract graph parts
  std::vector<Subgraph> parts = SubgraphExtractor::partitions(graph, \
      &bisection);
  ASSERT_EQUAL(parts.size(), NUM_BISECTION_PARTS);

  // recursively call execute
  for (pid_type part = 0; part < parts.size(); ++part) {
    double weightFrac = (static_cast<double>(bisection.getWeight(part)) / \
        static_cast<double>(graph->getTotalVertexWeight())) ;

    double const ratio = \
        bisectParams.getTargetPartitionFractions()[part] / weightFrac;
    
    PartitionParameters subParams(numHalfParts[part]);

    subParams.setImbalanceTolerance(params->getImbalanceTolerance() * ratio);
  }

  return partitioning;
}

}
