/**
* @file HeavyEdgeMatchingAggregation.hpp
* @brief The HeavyEdgeMatchingAggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-19
*/


#ifndef DOLOS_SRC_RANDOMMATCHINGAGGREGATOR_HPP
#define DOLOS_SRC_RANDOMMATCHINGAGGREGATOR_HPP


#include "util/IRandomEngine.hpp"
#include "aggregation/IAggregator.hpp"


namespace dolos
{


class HeavyEdgeMatchingAggregator : public IAggregator
{
  public:
    /**
    * @brief Create a new random matchign aggregator.
    *
    * @param randomEngine The random engine to use.
    */
    HeavyEdgeMatchingAggregator(
        IRandomEngine * const randomEngine);


    /**
    * @brief Deleted copy constructor.
    *
    * @param rhs The aggregator to copy.
    */
    HeavyEdgeMatchingAggregator(
        HeavyEdgeMatchingAggregator const & rhs) = delete;


    /**
    * @brief Deleted assignment operator.
    *
    * @param rhs The aggregator to copy from.
    *
    * @return This aggregator.
    */
    HeavyEdgeMatchingAggregator& operator=(
        HeavyEdgeMatchingAggregator const & rhs) = delete;


    /**
    * @brief Virtual destructor.
    */
    virtual ~HeavyEdgeMatchingAggregator();


    /**
    * @brief Generate an aggregation of the graph.
    *
    * @param graph The graph to aggregate.
    *
    * @return The aggregation.
    */
    virtual Aggregation aggregate(
        ConstantGraph const * graph) const;

  private:
    IRandomEngine * m_rng;
};


}

#endif
