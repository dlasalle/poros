/**
* @file TwoStepSummationContractor.cpp
* @brief Implementation of the TwoStepSummationContractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018-2026
* @version 1
* @date 2018-01-17
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




#include "TwoStepSummationContractor.hpp"
#include "Aggregation.hpp"
#include "graph/OneStepGraphBuilder.hpp"

#include "solidutils/Timer.hpp"


namespace poros
{



/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{

sl::Array<vtx_type> projectCmap(
    Graph const * const graph,
    Aggregation const * const aggregation)
{
  sl::Array<vtx_type> mappedEdges(graph->numEdges());

  for (Edge const edge : graph->edges()) {
    vtx_type const fineNeighbor = graph->destinationOf(edge).index;
    mappedEdges[edge.index] = aggregation->getCoarseVertexNumber(fineNeighbor);
  }

  return mappedEdges;
}

template<bool HAS_VERTEX_WEIGHTS, bool HAS_EDGE_WEIGHTS>
GraphHandle contractGraph(
    Graph const * const graph,
    Aggregation const * const aggregation,
    vtx_type const * const mappedEdges)
{
  OneStepGraphBuilder builder(
      aggregation->getNumCoarseVertices(),
      graph->numEdges());

  // go over each fine vertex
  for (VertexGroup const group : aggregation->coarseVertices()) {
    wgt_type coarseVertexWeight = 0;

    for (Vertex const vertex : group) {
      coarseVertexWeight += graph->weightOf<HAS_VERTEX_WEIGHTS>(vertex);
      for (Edge const edge : graph->edgesOf(vertex)) {
        vtx_type const coarseNeighbor = mappedEdges[edge.index];
        wgt_type const ewgt = graph->weightOf<HAS_EDGE_WEIGHTS>(edge);
        builder.addEdge(coarseNeighbor, ewgt);
      }
    }

    builder.finishVertex(coarseVertexWeight);
  }

  GraphHandle next = builder.finish();

  return next;
}

}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


TwoStepSummationContractor::TwoStepSummationContractor()
{
  // do nothing
}




/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


GraphHandle TwoStepSummationContractor::contract(
    Graph const * const graph,
    Aggregation const * const aggregation)
{
  sl::Array<vtx_type> const mappedEdges = projectCmap(graph, aggregation);

  if (graph->hasUnitVertexWeight()) {
    if (graph->hasUnitEdgeWeight()) {
      return contractGraph<false, false>(graph, aggregation, mappedEdges.data());
    } else {
      return contractGraph<false, true>(graph, aggregation, mappedEdges.data());
    }
  } else {
    if (graph->hasUnitEdgeWeight()) {
      return contractGraph<true, false>(graph, aggregation, mappedEdges.data());
    } else {
      return contractGraph<true, true>(graph, aggregation, mappedEdges.data());
    }
  }
}




}
