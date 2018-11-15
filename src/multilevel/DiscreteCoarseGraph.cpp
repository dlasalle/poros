/**
* @file DiscreteCoarseGraph.cpp
* @brief Implementation of the DiscreteCoarseGraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-15
*/

#include "multilevel/DiscreteCoarseGraph.hpp"
#include "aggregation/SummationContractor.hpp"

#include "solidutils/Timer.hpp"
#include <iostream>

namespace dolos
{

/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{

/**
* @brief Wrapper around the SummationContractor object.
*
* @param graph The graph to contract.
* @param agg The aggregation to use.
*
* @return The contracted graph.
*/
ConstantGraph contract(
  ConstantGraph const * graph,
  Aggregation const * agg)
{
  SummationContractor contractor;

  return contractor.contract(graph, agg);
}

}

/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

DiscreteCoarseGraph::DiscreteCoarseGraph(
  ConstantGraph const * graph,
  Aggregation const * agg) :
  m_fine(graph),
  m_coarse(contract(graph, agg)),
  m_coarseMap(graph->numVertices())
{
  agg->fillCoarseMap(m_coarseMap.data());
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


ConstantGraph const * DiscreteCoarseGraph::graph() const
{
  return &m_coarse;
}


Partitioning DiscreteCoarseGraph::project(
    Partitioning const * coarsePart)
{
  DEBUG_MESSAGE("Projecting partition from " +
      std::to_string(m_coarse.numVertices()) + " to " +
      std::to_string(m_fine->numVertices()));
  Partitioning finePart(coarsePart->numPartitions(), m_fine);

  sl::Timer tmr;
  tmr.start();

  // iterate over fine vertices
  for (Vertex const vertex : m_fine->vertices()) {
    vtx_type const v = vertex.index;
    vtx_type const c = m_coarseMap[v];
    pid_type const p = coarsePart->getAssignment(c); 

    finePart.assign(vertex, p); 
  }

  // TODO: this doesn't need to be calculated, we should set it directly
  finePart.recalcCutEdgeWeight();
  ASSERT_EQUAL(finePart.getCutEdgeWeight(), coarsePart->getCutEdgeWeight());

  tmr.stop();

  std::cout << "Projection took: " << tmr.poll() << std::endl;

  return finePart;
}




}

