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

#include <iostream>
#include "solidutils/Timer.hpp"

namespace poros
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


GraphHandle SummationContractor::contract(
    Graph const * const graph,
    Aggregation const * const aggregation)
{
  sl::Timer tmr;
  tmr.start();

  OneStepGraphBuilder builder(aggregation->getNumCoarseVertices(), graph->numEdges());

  // go over each fine vertex
  vtx_type coarseVertex = 0;
  for (VertexGroup const group : aggregation->coarseVertices()) {

    wgt_type coarseVertexWeight = 0;

    for (Vertex const vertex : group.fineVertices()) {
      coarseVertexWeight += graph->weightOf(vertex);
      for (Edge const edge : graph->edgesOf(vertex)) {
        vtx_type const coarseNeighbor = aggregation->getCoarseVertexNumber(
            graph->destinationOf(edge).index);
        if (coarseVertex != coarseNeighbor) {
          builder.addEdge(coarseNeighbor, graph->weightOf(edge));
        }
      }
    }

    builder.finishVertex(coarseVertexWeight);
    ++coarseVertex;
  }

  GraphHandle next = builder.finish();

  tmr.stop();
  std::cout << "Contract: " << tmr.poll() << std::endl;

  return next;
}




}
