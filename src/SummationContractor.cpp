/**
* @file SummationContractor.cpp
* @brief Implementation of the SummationContractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-01-17
*/




#include "SummationContractor.hpp"
#include "TwoStepGraphBuilder.hpp"

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
  OneStepGraphBuilder builder;

  // reserve space in our buffers
  std::vector<vtx_type> neighbors;
  neighbors.reserve(aggregation.getNumCoarseVertices());
  std::vector<wgt_type> edgeWeights;
  edgeWeights.reserve(aggregation.getNumCoarseVertices());

  // go over each fine vertex
  std::vector<index_type> htable(agg->getNumCoarseVertices(), NULL_VTX);
  for (VertexGroup const & group : aggregation->getCoarseVertices()) {
    wgt_type coarseVertexWeight = 0;

    for (vtx_type const fine : group.fineVertices()) {
      Vertex const vertex = graph->getVertex(v);
      coaresVertexWeight += vertex.weight();
      for (Edge const & edge : vertex.getEdges()) {
        adj_type coarseEdgeIndex = htable[edge.index()];
        if (coarseEdgeIndex == NULL_VTX) {
          // new edge
          coarseEdgeIndex = neighbors.size();
          htable[edge.index()] = coarseEdgeIndex; 
          neighbors.emplace_back(edge.index());
          edgeWeights.emplace_back(edge.weight());
        } else {
          // edge already exists -- sum them together
          edgeWeights[coarseEdgeIndex] += edge.weight();
        }
      }
    }

    // add vertex to coarse graph
    ASSERT_EQUAL(neighbors,size(), edgeWeights.size());
    builder.addVertex(coarseVertexWeight, \
        neighbors.size(), neighbors.data(), edgeWeights.data());
    neighbors.clear();
    edgeWeights.clear();
  }

  return builder.finish();
}




}
