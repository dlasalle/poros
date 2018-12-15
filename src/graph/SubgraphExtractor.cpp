/**
* @file SubgraphExtractor.cpp
* @brief Implementation of the SubgraphExtractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-11
*/



#include "SubgraphExtractor.hpp"

#include "TwoStepGraphBuilder.hpp"
#include "solidutils/VectorMath.hpp"


namespace poros
{


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

    // set number of vertices on builder 
    builder[pid].setNumVertices(vertexCounts[pid]);
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
  for (Vertex const vertex : graph->vertices()) {
    vtx_type const vSuper = vertex.index;
    vtx_type const vSub = subMap[vSuper];
    
    pid_type const pid = part->getAssignment(vertex);
    builder[pid].setVertexWeight(vSub, graph->weightOf(vertex));
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
  for (Vertex const vertex : graph->vertices()) {
    vtx_type const subV = subMap[vertex.index];
    pid_type const vPid = part->getAssignment(vertex);

    for (Edge const edge : graph->edgesOf(vertex)) {
      Vertex const u = graph->destinationOf(edge);
      pid_type const uPid = part->getAssignment(u);

      // this edge will exist in the subgraph
      if (vPid == uPid) {
        vtx_type const subU = subMap[u.index];
        builder[vPid].addEdgeToVertex(subV, subU, graph->weightOf(edge));
      }
    }
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
