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
#include "multilevel/CompositeStoppingCriteria.hpp"
#include "multilevel/EdgeRatioStoppingCriteria.hpp"
#include "multilevel/VertexNumberStoppingCriteria.hpp"


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
  CompositeStoppingCriteria criteria;

  criteria.add(std::unique_ptr<IStoppingCriteria>(
      new VertexNumberStoppingCriteria(target->numPartitions()*8)));
  criteria.add(std::unique_ptr<IStoppingCriteria>(
      new EdgeRatioStoppingCriteria(0.95)));

  return recurse(0, &criteria, target, nullptr, graph);
}


/******************************************************************************
* PROTECTED METHODS ***********************************************************
******************************************************************************/

Partitioning MultilevelBisector::recurse(
    int const level,
    IStoppingCriteria const * const stoppingCriteria,
    TargetPartitioning const * const target,
    ConstantGraph const * const parent,
    ConstantGraph const * const graph)
{
  if (stoppingCriteria->shouldStop(level, parent, graph)) {
    return m_initialBisector->execute(target, graph); 
  } else {
    Aggregation agg = m_aggregator->aggregate(graph);

    DiscreteCoarseGraph coarse(graph, &agg);

    // recurse
    Partitioning coarsePart = recurse(level+1,
        stoppingCriteria, target, graph, coarse.graph());

    Partitioning part = coarse.project(&coarsePart); 

    TwoWayConnectivity connectivity(graph, &part);

    m_refiner->refine(target, &connectivity, &part, graph);

    return part;
  }
}




}
