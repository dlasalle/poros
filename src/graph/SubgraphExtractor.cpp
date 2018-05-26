/**
* @file SubgraphExtractor.cpp
* @brief Implementation of the SubgraphExtractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-11
*/



#include "SubgraphExtractor.hpp"

#include "TwoStepGraphBuilder.hpp"
#include "solidutils/VectorMath.hpp"


namespace dolos
{


/******************************************************************************
* PUBLIC STATIC FUNCTIONS *****************************************************
******************************************************************************/


std::vector<Subgraph> SubgraphExtractor::partitions(
    ConstantGraph const * const graph,
    Partitioning const * const part,
    vtx_type const * const labels)
{
  pid_type const numParts = part->getNumPartitions();
  vtx_type const numVertices = graph->getNumVertices();

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
  for (vtx_type v = 0; v < numVertices; ++v) {
    pid_type const where = part->getAssignment(v);
    vtx_type const subV = vertexCounts[where]++;

    // assign sub to super
    if (labels) {
      superMaps[where][subV] = labels[v];
    } else {
      superMaps[where][subV] = v;
    }

    // assign super to sub
    subMap[v] = subV;
  }

  // fill vertex weights
  for (Vertex const & vertex : graph->vertices()) {
    vtx_type const vSuper = vertex.index();
    vtx_type const vSub = subMap[vSuper];
    
    pid_type const pid = part->getAssignment(vSuper);
    builder[pid].setVertexWeight(vSub, vertex.weight());
  }

  // calculate number of edges
  for (Vertex const & vertex : graph->vertices()) {
    vtx_type const v = vertex.index();
    vtx_type const subV = subMap[v];
    pid_type const vPid = part->getAssignment(v);

    for (Edge const & edge : vertex.edges()) {
      vtx_type const u = edge.destination();
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
  for (Vertex const & vertex : graph->vertices()) {
    vtx_type const v = vertex.index();
    vtx_type const subV = subMap[v];
    pid_type const vPid = part->getAssignment(v);

    for (Edge const & edge : vertex.edges()) {
      vtx_type const u = edge.destination();
      pid_type const uPid = part->getAssignment(u);

      // this edge will exist in the subgraph
      if (vPid == uPid) {
        vtx_type const subU = subMap[u];
        builder[vPid].addEdgeToVertex(subV, subU, edge.weight());
      }
    }
  }

  // assemble subgraphs
  std::vector<Subgraph> subgraphs;
  subgraphs.reserve(numParts);
  for (pid_type pid = 0; pid < numParts; ++pid) {
    ConstantGraph graph = builder[pid].finish();
    subgraphs.emplace_back(&graph, &superMaps[pid]);
  }

  return subgraphs;
}




}
