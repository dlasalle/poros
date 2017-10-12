/**
* @file SubgraphExtractor.cpp
* @brief Implementation of the SubgraphExtractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-11
*/



#include "SubgraphExtractor.hpp"

#include "GraphBuilder.hpp"
#include "ArrayUtils.hpp"


namespace dolos
{


/******************************************************************************
* PUBLIC STATIC FUNCTIONS *****************************************************
******************************************************************************/


std::vector<Subgraph> SubgraphExtractor::partitions(
    ConstantGraph const * const graph,
    Partitioning const * const part)
{
  pid_type const numParts = part->getNumPartitions();
  vtx_type const numVertices = graph->getNumVertices();

  // place to hold subgraphs while being constructed
  std::vector<GraphBuilder> builder(numParts);

  // count vertices in each partition
  std::vector<vtx_type> vertexCounts = part->calcVertexCounts();

  // map of sub graph vertices to super graph vertices 
  std::vector<Array<vtx_type>> map;
  for (pid_type part = 0; part < numParts; ++part) {
    ASSERT_EQUAL(map.size(), part);

    // allocate arrays for this subgraph
    map.emplace_back(vertexCounts[part]);

    // create builder for this partition

    // reset so we can populate the super-map
    vertexCounts[part] = 0;
  }

  // populate super-map and submap
  Array<vtx_type> subMap(numVertices);
  for (vtx_type v = 0; v < numVertices; ++v) {
    pid_type const where = part->getAssignment(v);
    vtx_type const subV = vertexCounts[where]++;

    // assign sub to super
    map[where][subV] = v;

    // assign super to sub
    subMap[v] = subV;
  }

  // calculate number of edges
  for (Vertex const & vertex : graph->getVertices()) {
    vtx_type const v = vertex.getIndex();
    vtx_type const subV = subMap[v];
    pid_type const vPart = part->getAssignment(v);

    for (Edge const & edge : vertex.getEdges()) {
      vtx_type const u = edge.getVertex();
      pid_type const uPart = part->getAssignment(u);

      // this edge will exist in the subgraph
      if (vPart == uPart) {
        ++edgePrefixes[vPart][subV]; 
      }
    }
  }

  // prefix sum edge counts for each partition
  for (pid_type part = 0; part < numParts; ++part) {
    ArrayUtils::prefixSumExclusive(&edgePrefixes[part]);
  }

  // allocate graph builder
  for (pid_type part = 0; part < numParts; ++part) {
    vtx_type const partVertices = vertexCounts[part];
    builder.emplace_back(partVertices, edgePrefixes[part][partVertices]);
  }

  // fill vertex weights
  for (Vertex const & vertex : graph->getVertices()) {
    vtx_type const vSuper = vertex.getIndex();
    vtx_type const vSub = subMap[vSuper];
    
    pid_type const part = part->getAssignment(vSuper);
    builder[part].setVertexWeight(vSub, vertex.getWeight());
  }

  // fill edges 
  for (Vertex const & vertex : graph->getVertices()) {
    vtx_type const v = vertex.getIndex();
    vtx_type const subV = subMap[v];
    pid_type const vPart = part->getAssignment(v);

    for (Edge const & edge : vertex.getEdges()) {
      vtx_type const u = edge.getVertex();
      pid_type const uPart = part->getAssignment(u);

      // this edge will exist in the subgraph
      if (vPart == uPart) {
        vtx_type const subU = subMap[u];
        builder[vPart].addEdgeToVertex(subV, subU, Edge.getWeight());
      }
    }
  }

  // assemble subgraphs
  std::vector<Subgraph> subgraphs;
  subgraphs.reserve(numParts);
  for (pid_type part = 0; part < numParts; ++part) {
    ConstantGraph graph = builder[part].finish();
    subgraphs.emplace_back(&graph, &map[part]);
  }

  return subgraphs;
}




}
