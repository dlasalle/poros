/**
* @file TimedAggregator.hpp
* @brief The TimedAggregator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
*/


#ifndef POROS_SRC_TIMEDAGGREGATOR_HPP
#define POROS_SRC_TIMEDAGGREGATOR_HPP


#include "IAggregator.hpp"
#include "util/TimedProcess.hpp"


namespace poros
{

class TimedAggregator : public IAggregator, public TimedProcess
{
  public:
    /**
    * @brief Create a new timed aggregator, wrapping an existing aggregator.
    *
    * @param aggregator The aggregator to wrap.
    */
    TimedAggregator(
        std::unique_ptr<IAggregator> aggregator);

    /**
    * @brief Create an aggregation of the graph.
    *
    * @param params The aggregation parameters.
    * @param graph The graph to aggregate.
    *
    * @return The aggregation.
    */
    Aggregation aggregate(
        AggregationParameters const params,
        Graph const * graph) override;

  private:
    std::unique_ptr<IAggregator> m_aggregator;


};


}

#endif

