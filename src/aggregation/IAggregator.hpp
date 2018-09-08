/**
* @file IAggregator.hpp
* @brief The IAggregator interface.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/




#ifndef DOLOS_SRC_IAGGREGATOR_HPP
#define DOLOS_SRC_IAGGREGATOR_HPP


#include "Aggregation.hpp"
#include "aggregation/AggregationParameters.hpp"
#include "graph/ConstantGraph.hpp"

namespace dolos
{

class IAggregator
{
  public:
    /**
    * @brief Virtual destructor to prevent memory leaks.
    */
    virtual ~IAggregator() 
    {
      // do nothing
    }

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
        ConstantGraph const * graph) = 0;

};

}

#endif
