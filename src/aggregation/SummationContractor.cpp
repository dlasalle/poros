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
  sl::Timer tmr;
  tmr.start();

  OneStepGraphBuilder builder(aggregation->getNumCoarseVertices(), graph->numEdges());

  // go over each fine vertex
  for (VertexGroup const group : aggregation->coarseVertices()) {
    wgt_type coarseVertexWeight = 0;

    for (Vertex const vertex : group.fineVertices()) {
      coarseVertexWeight += graph->weightOf(vertex);
      for (Edge const edge : graph->edgesOf(vertex)) {
        vtx_type const coarseNeighbor = aggregation->getCoarseVertexNumber(
            graph->destinationOf(edge).index);

        builder.addEdge(coarseNeighbor, graph->weightOf(edge));
      }
    }

    builder.finishVertex(coarseVertexWeight);
  }

  ConstantGraph next = builder.finish();

  tmr.stop();
  std::cout << "Contract: " << tmr.poll() << std::endl;

  return next;
}




}
