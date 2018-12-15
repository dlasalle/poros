/**
* @file IAggregator.hpp
* @brief The IAggregator interface.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-09
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
