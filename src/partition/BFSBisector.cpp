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

void moveBackUntilBalanced(
    Graph const * const graph,
    TargetPartitioning const * const target,
    Partitioning * const part,
    VertexQueue * const weightQueue)
{
  while (weightQueue->size() > 0) {
    Vertex const vertex = weightQueue->pop();
    wgt_type const newWeight = graph->weightOf(vertex) + part->getWeight(0);
    if (newWeight / static_cast<double>(target->getMaxWeight(0)) < \
        part->getWeight(1) / static_cast<double>(target->getMaxWeight(1))) {
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

  // move vertices based on edge connectivity
  while (queue.size() > 0 && part[0].weight() < target->getTargetWeight(0)) {
    // TODO queue should contain Vertex type
    Vertex const vertex = queue.pop();

    // We only make moves that will satisfy the balance constraint 
    if (graph->weightOf(vertex) + part[0].weight() <= target->getMaxWeight(0)) {
      part.move(vertex, 0);

      // update neighbor priority
      for (const Edge edge : graph->edgesOf(vertex)) {
        if (queue.contains(graph->destinationOf(edge))) {
          queue.updateByDelta(graph->weightOf(edge), graph->destinationOf(edge));
        }
      }
    }
  }

  if (part[1].weight() > target->getMaxWeight(1)) {
    // if we're still not at a balanced state, find the vertex with the
    // smallest weight to move over if it improves balance -- to do this
    // we add all remaining vertices to a new priority queue based on weight
    VertexQueue weightQueue(graph->numVertices());
    for (vtx_type const v : queue.remaining()) {
      Vertex const vertex = Vertex::make(v);
      weightQueue.add(graph->weightOf(vertex), vertex);
    }

    moveBackUntilBalanced(graph, target, &part, &weightQueue);
  }

  part.recalcCutEdgeWeight();

  return part;
}

}
