/**
* @file SubgraphExtractor.cpp
* @brief Implementation of the SubgraphExtractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-11
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



#include "SubgraphExtractor.hpp"

#include "TwoStepGraphBuilder.hpp"
#include "solidutils/VectorMath.hpp"


namespace poros
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{

template<bool HAS_VERTEX_WEIGHTS = true>
void fillVertexWeights(
    Graph const * const graph,
    Partitioning const * const part,
    vtx_type const * const subMap,
    TwoStepGraphBuilder * const builders)
{
  static_assert(HAS_VERTEX_WEIGHTS, \
      "Not valid to set vertex weights when vertex weights are unit");

  for (Vertex const vertex : graph->vertices()) {
    vtx_type const vSuper = vertex.index;
    vtx_type const vSub = subMap[vSuper];
    
    pid_type const pid = part->getAssignment(vertex);
    wgt_type const weight = graph->weightOf<HAS_VERTEX_WEIGHTS>(vertex);
    builders[pid].setVertexWeight(vSub, weight);
  }
}


template<bool HAS_EDGE_WEIGHTS>
void fillEdges(
    Graph const * const graph,
    Partitioning const * const part,
    vtx_type const * const subMap,
    TwoStepGraphBuilder * const builders)
{
  for (Vertex const vertex : graph->vertices()) {
    vtx_type const subV = subMap[vertex.index];
    pid_type const vPid = part->getAssignment(vertex);

    for (Edge const edge : graph->edgesOf(vertex)) {
      Vertex const u = graph->destinationOf(edge);
      pid_type const uPid = part->getAssignment(u);

      // this edge will exist in the subgraph
      if (vPid == uPid) {
        vtx_type const subU = subMap[u.index];
        wgt_type const weight = graph->weightOf<HAS_EDGE_WEIGHTS>(edge);
        builders[vPid].addEdgeToVertex(subV, subU, weight);
      }
    }
  }
}

}

/******************************************************************************
* PUBLIC STATIC FUNCTIONS *****************************************************
******************************************************************************/


std::vector<Subgraph> SubgraphExtractor::partitions(
    Graph const * const graph,
    Partitioning const * const part,
    vtx_type const * const labels)
{
  pid_type const numParts = part->numPartitions();
  vtx_type const numVertices = graph->numVertices();

  // place to hold subgraphs while being constructed
  std::vector<TwoStepGraphBuilder> builder(numParts);

  // count vertices in each partition
  std::vector<vtx_type> vertexCounts = part->calcVertexCounts();

  // map of sub graph vertices to super graph vertices 
  std::vector<sl::Array<vtx_type>> superMaps;
  for (pid_type pid = 0; pid < numParts; ++pid) {
    ASSERT_EQUAL(superMaps.size(), pid);

    // allocate arrays for this subgraph
    superMaps.emplace_back(vertexCounts[pid]);

    // configure each builder
    builder[pid].setNumVertices(vertexCounts[pid]);
    builder[pid].setUnitEdgeWeight(graph->hasUnitEdgeWeight());
    builder[pid].setUnitVertexWeight(graph->hasUnitVertexWeight());
    builder[pid].beginVertexPhase();

    // reset so we can populate the super-map
    vertexCounts[pid] = 0;
  }

  // populate super-map and submap
  sl::Array<vtx_type> subMap(numVertices);
  for (Vertex const v : graph->vertices()) {
    pid_type const where = part->getAssignment(v);
    vtx_type const subV = vertexCounts[where]++;

    // assign sub to super
    if (labels) {
      superMaps[where][subV] = labels[v.index];
    } else {
      superMaps[where][subV] = v.index;
    }

    // assign super to sub
    subMap[v.index] = subV;
  }

  // fill vertex weights
  if (!graph->hasUnitVertexWeight()) {
    fillVertexWeights(graph, part, subMap.data(), builder.data());
  }

  // calculate number of edges
  for (Vertex const vertex : graph->vertices()) {
    vtx_type const subV = subMap[vertex.index];
    pid_type const vPid = part->getAssignment(vertex);

    for (Edge const edge : graph->edgesOf(vertex)) {
      Vertex const u = graph->destinationOf(edge);
      pid_type const uPid = part->getAssignment(u);

      // this edge will exist in the subgraph
      if (vPid == uPid) {
        builder[vPid].incVertexNumEdges(subV);
      }
    }
  }

  // start edge phase
  for (pid_type pid = 0; pid < numParts; ++pid) {
    builder[pid].beginEdgePhase();
  }

  // fill edges 
  if (graph->hasUnitEdgeWeight()) {
    fillEdges<false>(graph, part, subMap.data(), builder.data());
  } else {
    fillEdges<true>(graph, part, subMap.data(), builder.data());
  }

  // assemble subgraphs
  std::vector<Subgraph> subgraphs;
  subgraphs.reserve(numParts);
  for (pid_type pid = 0; pid < numParts; ++pid) {
    GraphHandle subgraph = builder[pid].finish();
    subgraphs.emplace_back(subgraph, std::move(superMaps[pid]));
  }

  return subgraphs;
}




}
