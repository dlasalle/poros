/**
* @file BFSBisector.cpp
* @brief Implementation of the BFSBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-04
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


#include "BFSBisector.hpp"
#include "util/VertexQueue.hpp"

namespace poros
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{


template<bool HAS_VERTEX_WEIGHTS, bool HAS_EDGE_WEIGHTS>
void bfsPriorityMove(
    Graph const * const graph,
    TargetPartitioning const * const target,
    VertexQueue * const queue,
    Partitioning * const part)
{
  // move vertices based on edge connectivity
  while (queue->size() > 0 && \
      (*part)[0].weight() < target->getTargetWeight(0)) {
    // TODO queue should contain Vertex type
    Vertex const vertex = queue->pop();

    // We only make moves that will satisfy the balance constraint 
    if (graph->weightOf<HAS_VERTEX_WEIGHTS>(vertex) + \
        (*part)[0].weight() <= target->getMaxWeight(0)) {
      part->move(vertex, 0);

      // update neighbor priority
      for (const Edge edge : graph->edgesOf(vertex)) {
        if (queue->contains(graph->destinationOf(edge))) {
          queue->updateByDelta(graph->weightOf<HAS_EDGE_WEIGHTS>(edge), \
              graph->destinationOf(edge));
        }
      }
    }
  }
}


void bfsWeightBalance(
    Graph const * const graph,
    TargetPartitioning const * const target,
    VertexQueue::VertexSet const remaining,
    Partitioning * const part)
{
  // if we're still not at a balanced state, find the vertex with the
  // smallest weight to move over if it improves balance -- to do this
  // we add all remaining vertices to a new priority queue based on weight
  VertexQueue weightQueue(graph->numVertices());
  for (vtx_type const v : remaining) {
    Vertex const vertex = Vertex::make(v);
    weightQueue.add(graph->weightOf<true>(vertex), vertex);
  }

  while (weightQueue.size() > 0) {
    Vertex const vertex = weightQueue.pop();
    wgt_type const newWeight = graph->weightOf<true>(vertex) + \
        (*part)[0].weight();
    if (newWeight / static_cast<double>(target->getMaxWeight(0)) < \
        (*part)[1].weight() / static_cast<double>(target->getMaxWeight(1))) {
      part->move(vertex, 0);
      break;
    }
  }
}

void bfsUnitBalance(
    Graph const * const graph,
    TargetPartitioning const * const target,
    VertexQueue::VertexSet const remaining,
    Partitioning * const part)
{
  for (vtx_type const v : remaining) {
    Vertex const vertex = Vertex::make(v);

    wgt_type const newWeight = static_cast<wgt_type>(1) + (*part)[0].weight();
    if (newWeight / static_cast<double>(target->getMaxWeight(0)) < \
        (*part)[1].weight() / static_cast<double>(target->getMaxWeight(1))) {
      part->move(vertex, 0);
      break;
    }
  }
}

}

/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

BFSBisector::BFSBisector(
    RandomEngineHandle rng) : m_rng(rng)
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Partitioning BFSBisector::execute(
    TargetPartitioning const * target,
    Graph const * graph)
{
  Vertex const seedVertex = \
      Vertex::make(m_rng.randInRange(0, graph->numVertices()-1));

  return BFSBisector::execute(target, graph, seedVertex);
}

Partitioning BFSBisector::execute(
    TargetPartitioning const * target,
    Graph const * graph,
    Vertex const seed)
{
  ASSERT_EQUAL(target->numPartitions(), 2);

  Partitioning part(target->numPartitions(), graph);
    
  VertexQueue queue(graph->numVertices()); 

  // insert seed with weight of 1, and all others with weight of 0
  queue.add(static_cast<wgt_type>(1), seed);
  for (Vertex const v : graph->vertices()) {
    if (v != seed) {
      queue.add(static_cast<wgt_type>(0), v);
    }
  }

  part.assignAll(1);

  if (graph->hasUnitVertexWeight()) {
    if (graph->hasUnitEdgeWeight()) {
      bfsPriorityMove<false, false>(graph, target, &queue, &part);
    } else {
      bfsPriorityMove<false, true>(graph, target, &queue, &part);
    }
  } else {
    if (graph->hasUnitEdgeWeight()) {
      bfsPriorityMove<true, false>(graph, target, &queue, &part);
    } else {
      bfsPriorityMove<true, true>(graph, target, &queue, &part);
    }
  }

  if (part[1].weight() > target->getMaxWeight(1)) {
    if (graph->hasUnitVertexWeight()) {
      bfsWeightBalance(graph, target, queue.remaining(), &part);
    } else {
      bfsUnitBalance(graph, target, queue.remaining(), &part);
    }
  }

  part.recalcCutEdgeWeight();

  return part;
}

}
