/**
* @file RandomMatchingAggregator.hpp
* @brief The RandomMatchingAggregator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2017-11-09
*/




#ifndef DOLOS_SRC_RANDOMMATCHINGAGGREGATOR_HPP
#define DOLOS_SRC_RANDOMMATCHINGAGGREGATOR_HPP


#include "util/RandomEngineHandle.hpp"
#include "aggregation/IAggregator.hpp"


namespace dolos
{


class RandomMatchingAggregator : public IAggregator
{
  public:
    /**
    * @brief Create a new random matchign aggregator.
    *
    * @param randomEngine The random engine to use.
    */
    RandomMatchingAggregator(
        RandomEngineHandle randomEngine);


    /**
    * @brief Deleted copy constructor.
    *
    * @param rhs The aggregator to copy.
    */
    RandomMatchingAggregator(
        RandomMatchingAggregator const & rhs) = delete;


    /**
    * @brief Deleted assignment operator.
    *
    * @param rhs The aggregator to copy from.
    *
    * @return This aggregator.
    */
    RandomMatchingAggregator& operator=(
        RandomMatchingAggregator const & rhs) = delete;


    /**
    * @brief Virtual destructor.
    */
    virtual ~RandomMatchingAggregator();


    /**
    * @brief Generate an aggregation of the graph.
    *
    * @param params The aggregation parameters.
    * @param graph The graph to aggregate.
    *
    * @return The aggregation.
    */
   Aggregation aggregate(
        AggregationParameters params,
        ConstantGraph const * graph) override;

  private:
    RandomEngineHandle m_rng;
};


}

#endif
