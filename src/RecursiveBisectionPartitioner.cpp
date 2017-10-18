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



namespace dolos
{


/******************************************************************************
* PRIVATE METHODS *************************************************************
******************************************************************************/

void RecursiveBisectionPartitioner::recurse(
    Partitioning * const superPartitioning,
    PartitionParameters const * const params,
    Subgraph const * subGraph,
    pid_type const offset) const
{
  ConstantGraph const * const graph = subGraph->getGraph();
  
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

  // calculate the target weight for each side
  // bisect
  Partitioning bisection = m_bisector->execute(&bisectParams, graph);
  subGraph->mapPartitioning(&bisection, superPartitioning, offset);

  if (numParts > 2) {
    std::vector<pid_type> numPartsPrefix(3);
    numPartsPrefix[0] = 0;
    numPartsPrefix[1] = numParts / 2;
    numPartsPrefix[2] = numParts;

    // extract graph parts
    std::vector<Subgraph> parts = SubgraphExtractor::partitions(graph, \
        &bisection);
    ASSERT_EQUAL(parts.size(), NUM_BISECTION_PARTS);

    // recursively call execute
    for (pid_type part = 0; part < parts.size(); ++part) {
      pid_type const numHalfParts = numPartsPrefix[part+1] - \
          numPartsPrefix[part];
      if (numHalfParts > 1) {
        double weightFrac = (static_cast<double>(bisection.getWeight(part)) / \
            static_cast<double>(graph->getTotalVertexWeight())) ;

        double const ratio = \
            bisectParams.getTargetPartitionFractions()[part] / weightFrac;
        
        PartitionParameters subParams(numHalfParts);

        subParams.setImbalanceTolerance(params->getImbalanceTolerance() * \
            ratio);

        recurse(superPartitioning, &subParams, &(parts[part]), \
            offset+numPartsPrefix[part]);
      }
    }
  } else {
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
  // ideally we'd like this function to use something close to tail recursion,
  // where its last invocation will write the correct partition id's to the
  // assignment vector


  Partitioning partitioning(params->getNumPartitions(), graph);

  return partitioning;
}

}
