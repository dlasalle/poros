/**
* @file BFSBisector.cpp
* @brief Implementation of the BFSBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-04
*/


#include "BFSBisector.hpp"

#include "solidutils/FixedPriorityQueue.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

BFSBisector::BFSBisector(
    IRandomEngine * const rng) : m_rng(rng)
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Partitioning BFSBisector::execute(
    TargetPartitioning const * target,
    ConstantGraph const * graph) const
{
  vtx_type const seed = m_rng->randInRange(0, graph->numVertices()-1);

  return BFSBisector::execute(target, graph, seed);
}

Partitioning BFSBisector::execute(
    TargetPartitioning const * target,
    ConstantGraph const * graph,
    vtx_type const seed) const
{
  ASSERT_EQUAL(target->numPartitions(), 2);

  Partitioning part(target->numPartitions(), graph);
    
  sl::FixedPriorityQueue<wgt_type, vtx_type> queue(graph->numVertices()); 

  // insert seed with weight of 1, and all others with weight of 0
  queue.add(static_cast<wgt_type>(1), seed);
  for (const Vertex v : graph->vertices()) {
    vtx_type const other = v.index();
    if (other != seed) {
      queue.add(static_cast<wgt_type>(0), other);
    }
  }

  part.assignAll(1);

  // move vertices based on edge connectivity
  while (queue.size() > 0 && part[0].weight() < target->getTargetWeight(0)) {
    vtx_type const v = queue.pop();
    Vertex const vertex = graph->getVertex(v);

    // We only make moves that will satisfy the balance constraint 
    if (vertex.weight() + part[0].weight() <= target->getMaxWeight(0)) {
      part.move(v, 0);

      // update neighbor priority
      for (const Edge edge : vertex.edges()) {
        if (queue.contains(edge.destination())) {
          queue.updateByDelta(edge.weight(), edge.destination());
        }
      }
    }
  }

  if (part[1].weight() > target->getMaxWeight(1)) {
    // if we're still not at a balanced state, find the vertex with the
    // smallest weight to move over if it improves balance -- to do this
    // we add all remaining vertices to a new priority queue based on weight
    sl::FixedPriorityQueue<wgt_type, vtx_type> weightQueue(graph->numVertices());
    for (vtx_type const v : queue.remaining()) {
      Vertex const vertex = graph->getVertex(v);
      weightQueue.add(vertex.weight(), v);
    }

    while (weightQueue.size() > 0) {
      vtx_type const v = queue.pop();
      Vertex const vertex = graph->getVertex(v);
      wgt_type const newWeight = vertex.weight() + part[0].weight();
      if (newWeight / static_cast<double>(target->getMaxWeight(0)) < \
          part[1].weight() / static_cast<double>(target->getMaxWeight(1))) {
        part.move(v, 0);
        break;
      }
    }
  }

  part.recalcCutEdgeWeight();

  return part;
}



}
