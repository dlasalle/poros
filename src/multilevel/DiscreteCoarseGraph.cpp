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
#include "partition/TwoWayConnectivityBuilder.hpp"

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
GraphHandle contract(
  Graph const * graph,
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
  Graph const * graph,
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


Graph const * DiscreteCoarseGraph::graph() const
{
  return m_coarse.get();
}


PartitioningInformation DiscreteCoarseGraph::project(
    PartitioningInformation const * const info)
{
  Partitioning const * const coarsePart = info->partitioning();
  TwoWayConnectivity const * const coarseConn = info->connectivity();

  DEBUG_MESSAGE("Projecting partition from " +
      std::to_string(m_coarse->numVertices()) + " to " +
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

  TwoWayConnectivityBuilder connBuilder;
  
  connBuilder.begin(m_fine->numVertices());

  // build connectivity
  for (Vertex const vertex : m_fine->vertices()) {
    vtx_type const v = vertex.index;
    vtx_type const c = m_coarseMap[v];
    if (coarseConn->isInBorder(c)) {
      vtx_type const home = finePart.getAssignment(vertex);
      wgt_type internal = 0;
      wgt_type external = 0;
      // coarse vertex was in the border -- so this one might be
      for (Edge const edge : m_fine->edgesOf(vertex)) {
        vtx_type const neighbor = m_fine->destinationOf(edge);
        pid_type const neighborPartition = finePart.getAssignment(neighbor);
        wgt_type const weight = m_fine->weightOf(edge);
        if (neighborPartition == home) {
          // internal weight
          internal += weight;
        } else {
          // external weight
          external += weight;
        }
      }
      connBuilder.setInternalConnectivityOf(vertex, internal);
      connBuilder.setExternalConnectivityOf(vertex, external);
    } else {
      // coarse vertex was not in the border, so just sum edge weight
      wgt_type sum = 0;
      for (Edge const edge : m_fine->edgesOf(vertex)) {
        sum += m_fine->weightOf(edge);
      }
      connBuilder.setInternalConnectivityOf(vertex, sum);
      connBuilder.setExternalConnectivityOf(vertex, 0);
    }
  }

  finePart.setCutEdgeWeight(coarsePart->getCutEdgeWeight());
  ASSERT_EQUAL(finePart.getCutEdgeWeight(), coarsePart->getCutEdgeWeight());

  tmr.stop();

  std::cout << "Projection took: " << tmr.poll() << std::endl;

  return PartitioningInformation(std::move(finePart), connBuilder.finish());
}




}

