/**
* @file SummationContractor.hpp
* @brief The SummationContractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-01-17
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




#ifndef POROS_SRC_SUMMATIONCONTRACTOR_HPP
#define POROS_SRC_SUMMATIONCONTRACTOR_HPP


#include "aggregation/IContractor.hpp"


namespace poros
{

class SummationContractor : public IContractor
{
  public:
    /**
    * @brief Create a new summation contractor.
    */
    SummationContractor();


    /**
    * @brief Contract a graph, dropping contracted edge weights, summing
    * combined vertex weights, and summing combined edge weights. 
    *
    * @param graph The graph to contract.
    * @param aggregation The aggregation specifying which vertices to aggregate
    * together.
    *
    * @return The contracted graph.
    */
    GraphHandle contract(
        Graph const * graph,
        Aggregation const * aggregation) override;
};




}




#endif
