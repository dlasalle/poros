/**
* @file SubgraphExtractor.cpp
* @brief Implementation of the SubgraphExtractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-11
*/



#include "SubgraphExtractor.hpp"

#include "GraphData.hpp"
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
  // place to hold subgraphs while being constructed
  std::vector<GraphData> data;

  // place to hold super-mapping during construction
  std::vector<Array<vtx_type>> map;

  pid_type const numParts = part->getNumPartitions();
  vtx_type const numVertices = graph->getNumVertices();

  // count vertices in each partition
  std::vector<vtx_type> vertexCounts = part->calcVertexCounts();

  std::vector<Array<adj_type>> edgePrefixes;
  for (pid_type part = 0; part < numParts; ++part) {
    ASSERT_EQUAL(edgePrefixes.size(), part);
    ASSERT_EQUAL(map.size(), part);

    // allocate arrays for this subgraph
    map.emplace_back(vertexCounts[part]);

    edgePrefixes.emplace_back(vertexCounts[part]+1);
    edgePrefixes[part].set(0);

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


  // assemble subgraphs
  std::vector<Subgraph> subgraphs;
  subgraphs.reserve(numParts);
  for (pid_type part = 0; part < numParts; ++part) {
    ConstantGraph graph = data[part].toGraph();
    subgraphs.emplace_back(&graph, &map[part]);
  }

  return subgraphs;
}




}
