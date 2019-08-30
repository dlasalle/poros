/**
* @file RecursiveBisectionPartitioner.cpp
* @brief Implementation of the RecursiveBisectionPartitioner.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-10
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


#include "RecursiveBisectionPartitioner.hpp"

#include "graph/MappedGraphWrapper.hpp"
#include "graph/SubgraphExtractor.hpp"
#include "partition/TargetPartitioning.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "solidutils/VectorMath.hpp"

#include <cmath>
#include <string>

namespace poros
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
  Graph const * const graph = mappedGraph->getGraph();
  
  pid_type const numParts = target->numPartitions();

  // We don't want to use the k-way imbalance tolerance, as if one half of the
  // bisection is at maximum weight, then each partition with in that half must
  // also be at maximum weight (in the case of non-uniform vertex weights we
  // may find it impossible to balance). So instead, what we do is use
  // \eps / \log_2(k)
  double const toleranceFactor = 1.0 / std::log2(target->numPartitions());

  // calculate target fractions
  sl::Array<pid_type> numPartsPrefix(3);
  numPartsPrefix.set(0);

  sl::Array<wgt_type> targetBisectWeights(NUM_BISECTION_PARTS, 0);
  sl::Array<wgt_type> maxBisectWeights(NUM_BISECTION_PARTS, 0);
  for (pid_type pid = 0; pid < numParts; ++pid) {
    // we must put a larger or equal number of partitions in the second half
    pid_type const half = static_cast<pid_type>(pid >= numParts/2);
    targetBisectWeights[half] += target->getTargetWeight(pid);
    maxBisectWeights[half] += target->getTargetWeight(pid) +
        (target->getMaxExcessWeight(pid)*toleranceFactor);
    ++numPartsPrefix[half];
  }

  sl::VectorMath::prefixSumExclusive(numPartsPrefix.data(), \
      numPartsPrefix.size());

  // build parameters for bisection
  TargetPartitioning bisectTarget(NUM_BISECTION_PARTS, \
      std::move(targetBisectWeights), std::move(maxBisectWeights));

  // calculate the target weight for each side bisect
  Partitioning bisection = m_bisector->execute(&bisectTarget, graph);
  PartitioningAnalyzer analyzer(&bisection, &bisectTarget);

  DEBUG_MESSAGE(std::string("Made bisection of balance ") + \
      std::to_string(analyzer.calcMaxImbalance()) + \
      std::string(" (") + \
      std::to_string(bisection.getWeight(LEFT_PARTITION)) + \
      std::string("/") + \
      std::to_string(bisectTarget.getMaxWeight(LEFT_PARTITION)) + \
      std::string(":") + \
      std::to_string(bisection.getWeight(RIGHT_PARTITION)) + std::string("/") + \
      std::to_string(bisectTarget.getMaxWeight(RIGHT_PARTITION)) + \
      std::string(")"));

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

    for (pid_type part = 0; static_cast<size_t>(part) < parts.size(); ++part) {
      pid_type const numHalfParts = numPartsPrefix[part+1] - \
          numPartsPrefix[part];

      if (numHalfParts > 1) {
        // recursively call execute
        sl::Array<wgt_type> halfWeights(numHalfParts);
        sl::Array<wgt_type> halfMaxs(numHalfParts);
        for (pid_type pid = 0; pid < numHalfParts; ++pid) {
          pid_type const offset = numPartsPrefix[part];
          halfWeights[pid] = target->getTargetWeight(pid+offset);
          halfMaxs[pid] = target->getMaxWeight(pid+offset);
        }
        TargetPartitioning subTarget(numHalfParts, \
            std::move(halfWeights),
            std::move(halfMaxs));

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
    Graph const * const graph)
{
  sl::Array<pid_type> partitionLabels(graph->numVertices());

  MappedGraphWrapper mappedGraph(graph);
  recurse(partitionLabels.data(), target, &mappedGraph, 0);

  Partitioning part(target->numPartitions(), graph, std::move(partitionLabels));
  part.recalcCutEdgeWeight();

  return part;
}

}
