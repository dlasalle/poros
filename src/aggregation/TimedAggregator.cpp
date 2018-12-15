/**
* @file TimedAggregator.cpp
* @brief Implementation of the TimedAggregator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
*/

#include "TimedAggregator.hpp"

#include "solidutils/Timer.hpp"

namespace poros
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

TimedAggregator::TimedAggregator(
    std::unique_ptr<IAggregator> aggregator) :
  m_aggregator(std::move(aggregator))
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Aggregation TimedAggregator::aggregate(
    AggregationParameters const params,
    Graph const * const graph)
{
  sl::Timer tmr;
  tmr.start();

  Aggregation agg = m_aggregator->aggregate(params, graph);

  tmr.stop();

  reportTime(TimeKeeper::AGGREGATION, tmr.poll());

  return agg;
}


}

