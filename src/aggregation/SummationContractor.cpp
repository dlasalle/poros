/**
* @file SummationContractor.cpp
* @brief Implementation of the SummationContractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-01-17
*/




#include "SummationContractor.hpp"
#include "graph/OneStepGraphBuilder.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


SummationContractor::SummationContractor()
{
  // do nothing
}




/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


ConstantGraph SummationContractor::contract(
    ConstantGraph const * const graph,
    Aggregation const * const aggregation)
{
  OneStepGraphBuilder builder(
      aggregation->getNumCoarseVertices(),
      graph->numEdges());

  // reserve space in our buffers
  std::vector<vtx_type> neighbors;
  neighbors.reserve(aggregation->getNumCoarseVertices());
  std::vector<wgt_type> edgeWeights;
  edgeWeights.reserve(aggregation->getNumCoarseVertices());

  // go over each fine vertex
  vtx_type coarseVertexNumber = 0;
  std::vector<vtx_type> htable(aggregation->getNumCoarseVertices(), NULL_VTX);
  for (VertexGroup const group : aggregation->coarseVertices()) {
    wgt_type coarseVertexWeight = 0;

    for (Vertex const vertex : group.fineVertices()) {
      coarseVertexWeight += graph->weightOf(vertex);
      for (Edge const edge : graph->edgesOf(vertex)) {
        vtx_type const coarseNeighbor = aggregation->getCoarseVertexNumber(
            graph->destinationOf(edge).index);
        if (coarseNeighbor == coarseVertexNumber) {
          // skip self loops
          continue;
        }

        adj_type coarseEdgeIndex = htable[coarseNeighbor];
        if (coarseEdgeIndex == NULL_VTX) {
          // new edge
          coarseEdgeIndex = neighbors.size();
          htable[coarseNeighbor] = coarseEdgeIndex; 
          neighbors.emplace_back(coarseNeighbor);
          edgeWeights.emplace_back(
              graph->weightOf(edge));
        } else {
          // edge already exists -- sum them together
          edgeWeights[coarseEdgeIndex] += graph->weightOf(edge);
        }
      }
    }

    ++coarseVertexNumber;

    // add vertex to coarse graph
    ASSERT_EQUAL(neighbors.size(), edgeWeights.size());
    builder.addVertex(coarseVertexWeight, \
        neighbors.size(), neighbors.data(), edgeWeights.data());

    // clear hash table
    for (vtx_type const neighbor : neighbors) {
      htable[neighbor] = NULL_VTX;
    }

    neighbors.clear();
    edgeWeights.clear();
  }

  return builder.finish();
}




}
