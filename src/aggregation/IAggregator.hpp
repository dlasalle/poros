/**
* @file IAggregator.hpp
* @brief The IAggregator interface.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-09
*/




#ifndef POROS_SRC_IAGGREGATOR_HPP
#define POROS_SRC_IAGGREGATOR_HPP


#include "Aggregation.hpp"
#include "aggregation/AggregationParameters.hpp"
#include "graph/Graph.hpp"

namespace poros
{

class IAggregator
{
  public:
    /**
    * @brief Virtual destructor to prevent memory leaks.
    */
    virtual ~IAggregator() = default;

    /**
    * @brief Create an aggregation of the graph.
    *
    * @param params The aggregation parameters.
    * @param graph The graph to aggregate.
    *
    * @return The aggregation.
    */
    virtual Aggregation aggregate(
        AggregationParameters params,
        Graph const * graph) = 0;

};

}

#endif
