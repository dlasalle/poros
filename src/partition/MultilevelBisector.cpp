/**
* @file MultilevelBisector.cpp
* @brief Implementation of the MultilevelBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-09
*/


#include "partition/MultilevelBisector.hpp"
#include "multilevel/DiscreteCoarseGraph.hpp"
#include "partition/TwoWayConnectivity.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

MultilevelBisector::MultilevelBisector(
    std::unique_ptr<IAggregator> aggregator,
    std::unique_ptr<IBisector> initialBisector,
    std::unique_ptr<ITwoWayRefiner> refiner) :
  m_aggregator(std::move(aggregator)),
  m_initialBisector(std::move(initialBisector)),
  m_refiner(std::move(refiner))
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Partitioning MultilevelBisector::execute(
    TargetPartitioning const * target,
    ConstantGraph const * graph)
{
  Aggregation agg = m_aggregator->aggregate(graph);

  DiscreteCoarseGraph coarse(graph, &agg);

  // recurse
  Partitioning coarsePart = execute(target, coarse.graph());

  Partitioning part = coarse.project(&coarsePart); 

  TwoWayConnectivity connectivity(graph, &part);

  m_refiner->refine(target, &connectivity, &part, graph);

  return part;
}




}
