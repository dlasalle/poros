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



#include "IAggregator.hpp"
#include "IRandomEngine.hpp"


namespace dolos
{


class RandomMatchingAggregator
{
  public:
    /**
    * @brief Create a new random matchign aggregator.
    */
    RandomMatchingAggregator();


    /**
    * @brief Virtual destructor.
    */
    virtual ~RandomMatchingAggregator();


    /**
    * @brief Generate an aggregation of the graph.
    *
    * @param graph The graph to aggregate.
    *
    * @return The aggregation.
    */
    virtual Aggregation aggregate(
        ConstantGraph const * graph,
        IRandomEngine * const randomEngine) const;


};


}

#endif
