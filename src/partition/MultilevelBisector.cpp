/**
* @file MultilevelBisector.cpp
* @brief Implementation of the MultilevelBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-09
*/


#include "partition/MultilevelBisector.hpp"


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
  m_intialBisector(std::move(initialBisector)),
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
  Aggregation agg = m_aggregator->execute(graph);

  SummationCoarsener coarsener;

  coarsener.coarsen(graph, agg);

  Partitioning coarsePart = execute(target, coarsener.coarse());

  Partitioning part = coarsener.uncoarsen(coarsePart); 

  m_refiner->refine(target, connectivity, &part, graph);

  return part;
}




}
