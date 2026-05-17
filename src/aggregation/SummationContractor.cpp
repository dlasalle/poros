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

template<bool HAS_VERTEX_WEIGHTS, bool HAS_EDGE_WEIGHTS>
GraphHandle contractGraph(
    Graph const * const graph,
    Aggregation const * const aggregation)
{
  sl::Timer t;
  t.start();
  OneStepGraphBuilder builder(aggregation->getNumCoarseVertices(), graph->numEdges());

  #if 0
  // go over each fine vertex
  vtx_type coarseVertex = 0;
  for (VertexGroup const group : aggregation->coarseVertices()) {
    wgt_type coarseVertexWeight = 0;

    for (Vertex const vertex : group) {
      ASSERT_EQUAL(coarseVertex, \
          aggregation->getCoarseVertexNumber(vertex.index));
      coarseVertexWeight += graph->weightOf<HAS_VERTEX_WEIGHTS>(vertex);
      for (Edge const edge : graph->edgesOf(vertex)) {
        vtx_type const coarseNeighbor = aggregation->getCoarseVertexNumber(
            graph->destinationOf(edge).index);
        wgt_type const ewgt = graph->weightOf<HAS_EDGE_WEIGHTS>(edge);
        builder.addEdge(coarseNeighbor, ewgt);
      }
    }

    builder.finishVertex(coarseVertexWeight);
    ++coarseVertex;
  }

  GraphHandle next = builder.finish();
  #else
  vtx_type const * const finePrefix = aggregation->finePrefix();
  vtx_type const * const fineMap = aggregation->fineMap();
  vtx_type const * const coarseMap = aggregation->cmap();

  wgt_type const * const vertexWeight = graph->getVertexWeight();

  adj_type const * const edgePrefix = graph->getEdgePrefix();
  vtx_type const * const edgeList = graph->getEdgeList();
  wgt_type const * const edgeWeight = graph->getEdgeWeight();

  // allocate new graph
  sl::Array<adj_type> newEdgePrefix(aggregation->getNumCoarseVertices()+1);
  sl::Array<vtx_type> newEdgeList(graph->numEdges()+1);
  sl::Array<wgt_type> newVertexWeight(aggregation->getNumCoarseVertices()+1);
  sl::Array<wgt_type> newEdgeWeight(graph->numEdges()+1);

  std::vector<adj_type> htable(aggregation->getNumCoarseVertices()+1, NULL_ADJ);
  htable[0] = 0;
  newEdgePrefix[0] = 0;
  newEdgeList[0] = 0;
  newEdgeWeight[0] = 0;

  vtx_type numVertices = 0;
  adj_type numEdges = 1;

  vtx_type const numCoarseVertices = aggregation->getNumCoarseVertices();
  for (vtx_type coarseVertex = 0; coarseVertex < numCoarseVertices; ++coarseVertex) {
    wgt_type coarseVertexWeight = 0;
    for (vtx_type i = finePrefix[coarseVertex]; i < finePrefix[coarseVertex+1]; ++i) {
      vtx_type const vertex = fineMap[i];
      if (HAS_VERTEX_WEIGHTS) {
        coarseVertexWeight += vertexWeight[vertex];
      } else {
        ++coarseVertexWeight;
      }
      for (adj_type j = edgePrefix[vertex]; j < edgePrefix[vertex+1]; ++j) {
        vtx_type const nbr = edgeList[j];
        vtx_type const coarseNeighbor = coarseMap[nbr]; 

        adj_type const idx = htable[coarseNeighbor];
        wgt_type const wgt = HAS_EDGE_WEIGHTS ? edgeWeight[j] : 1;
        if (idx == NULL_ADJ) {
          htable[coarseNeighbor] = numEdges;
          newEdgeList[numEdges] = coarseNeighbor;
          newEdgeWeight[numEdges] = wgt;
          ++numEdges;
        } else {
          newEdgeWeight[idx] += wgt;
        }
      }
    }

    vtx_type const thisVtx = numVertices;
    ++numVertices;

    adj_type const firstEdge = newEdgePrefix[thisVtx];
    for (vtx_type j = firstEdge; j < numEdges; ++j) {
      vtx_type const u = newEdgeList[j];
      htable[u] = NULL_ADJ;
    }

    adj_type const lastEdge = numEdges-1;
    
    // clear self-loop
    newEdgeList[firstEdge] = newEdgeList[lastEdge];
    newEdgeWeight[firstEdge] = newEdgeWeight[lastEdge];

    newVertexWeight[thisVtx] = coarseVertexWeight;
    newEdgePrefix[numVertices] = lastEdge;

    // set next self-loop
    htable[numVertices] = lastEdge;
    newEdgeList[lastEdge] = numVertices;
    newEdgeWeight[lastEdge] = 0;

    //printf("Finished vertex %d: %d\n", numVertices, numEdges);
  }

  --numEdges;
  newEdgeList.shrink(numEdges);
  newEdgeWeight.shrink(numEdges);

  // compute totals separate
  wgt_type totalVertexWeight= 0;
  for (vtx_type i = 0; i < numVertices; ++i) {
    totalVertexWeight += newVertexWeight[i];
  }

  wgt_type totalEdgeWeight = 0;
  for (adj_type i = 0; i < numEdges; ++i) {
    totalEdgeWeight += newEdgeWeight[i];
  }

  GraphHandle next(Graph(
      std::move(newEdgePrefix),
      std::move(newEdgeList),
      std::move(newVertexWeight),
      std::move(newEdgeWeight),
      totalVertexWeight,
      totalEdgeWeight,
      false,
      false));
  ASSERT_TRUE(next->isValid());
  #endif

  t.stop();

  if (HAS_EDGE_WEIGHTS && HAS_VERTEX_WEIGHTS) {
    printf("Using full weights\n");
  }
  if (!HAS_EDGE_WEIGHTS && !HAS_VERTEX_WEIGHTS) {
    printf("Using no weights\n");
  }
  printf("Contract time: %0.05fs\n", t.poll());

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
  if (false && graph->hasUnitVertexWeight()) {
    if (graph->hasUnitEdgeWeight()) {
      return contractGraph<false, false>(graph, aggregation);
    } else {
      return contractGraph<false, true>(graph, aggregation);
    }
  } else {
    if (false && graph->hasUnitEdgeWeight()) {
      return contractGraph<true, false>(graph, aggregation);
    } else {
      return contractGraph<true, true>(graph, aggregation);
    }
  }
}




}
