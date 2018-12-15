/**
* @file SummationContractor.cpp
* @brief Implementation of the SummationContractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
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




#include "SummationContractor.hpp"
#include "graph/OneStepGraphBuilder.hpp"


namespace poros
{



/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{

template<bool UNIT_VERTICES, bool UNIT_EDGES>
GraphHandle contractGraph(
    Graph const * const graph,
    Aggregation const * const aggregation)
{
  OneStepGraphBuilder builder(aggregation->getNumCoarseVertices(), graph->numEdges());

  // go over each fine vertex
  vtx_type coarseVertex = 0;
  for (VertexGroup const group : aggregation->coarseVertices()) {

    wgt_type coarseVertexWeight = 0;

    for (Vertex const vertex : group.fineVertices()) {
      if (UNIT_VERTICES) {
        coarseVertexWeight += static_cast<wgt_type>(1);
      } else {
        coarseVertexWeight += graph->weightOf(vertex);
      }
      for (Edge const edge : graph->edgesOf(vertex)) {
        vtx_type const coarseNeighbor = aggregation->getCoarseVertexNumber(
            graph->destinationOf(edge).index);
        if (coarseVertex != coarseNeighbor) {
          if (UNIT_EDGES) {
            builder.addEdge(coarseNeighbor, static_cast<wgt_type>(1));
          } else {
            builder.addEdge(coarseNeighbor, graph->weightOf(edge));
          }
        }
      }
    }

    builder.finishVertex(coarseVertexWeight);
    ++coarseVertex;
  }

  GraphHandle next = builder.finish();

  return next;
}






}


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


GraphHandle SummationContractor::contract(
    Graph const * const graph,
    Aggregation const * const aggregation)
{
  if (graph->hasUnitVertexWeight()) {
    if (graph->hasUnitEdgeWeight()) {
      return contractGraph<true, true>(graph, aggregation);
    } else {
      return contractGraph<true, false>(graph, aggregation);
    }
  } else {
    if (graph->hasUnitEdgeWeight()) {
      return contractGraph<false, true>(graph, aggregation);
    } else {
      return contractGraph<false, false>(graph, aggregation);
    }
  }
}




}
