/**
* @file HeavyEdgeMatchingAggregation.hpp
* @brief The HeavyEdgeMatchingAggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-19
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/


#ifndef POROS_SRC_HEAVYEDGEMATCHINGAGGREGATOR_HPP
#define POROS_SRC_HEAVYEDGEMATCHINGAGGREGATOR_HPP


#include "util/RandomEngineHandle.hpp"
#include "aggregation/IAggregator.hpp"


namespace poros
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
        RandomEngineHandle randomEngine);


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
    virtual ~HeavyEdgeMatchingAggregator() = default;


    /**
    * @brief Generate an aggregation of the graph.
    *
    * @param graph The graph to aggregate.
    *
    * @return The aggregation.
    */
    Aggregation aggregate(
        AggregationParameters params,
        Graph const * graph);

  private:
    RandomEngineHandle m_rng;
};


}

#endif
