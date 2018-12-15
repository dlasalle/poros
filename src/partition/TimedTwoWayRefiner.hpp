/**
* @file TimedTwoWayRefiner.hpp
* @brief The TimedTwoWayRefiner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
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


#ifndef POROS_SRC_TIMEDTWOWAYREFINER_HPP
#define POROS_SRC_TIMEDTWOWAYREFINER_HPP

#include "ITwoWayRefiner.hpp"
#include "util/TimedProcess.hpp"

namespace poros
{

class TimedTwoWayRefiner : public ITwoWayRefiner, public TimedProcess
{
  public:
    /**
    * @brief Create a new time two way refiner.
    *
    * @param refiner The refiner to wrap.
    */
    TimedTwoWayRefiner(
        std::unique_ptr<ITwoWayRefiner> refiner);

    /**
    * @brief Refine the partition for the given graph.
    *
    * @param params The parameters of the bisection.
    * @param partitioning The partitioning (input and output).
    * @param connectivity The connectivity of vertices to the partitions.
    * @param graph The graph.
    */
    void refine(
        TargetPartitioning const * target,
        TwoWayConnectivity * connectivity,
        Partitioning * partitioning,
        Graph const * graph) override;

    private:
      std::unique_ptr<ITwoWayRefiner> m_refiner;
};

}

#endif

