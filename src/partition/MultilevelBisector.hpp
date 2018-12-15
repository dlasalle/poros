/**
* @file MultilevelBisector.hpp
* @brief The MultilevelBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-09
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



#ifndef POROS_SRC_MULTILEVELBISECTOR_HPP
#define POROS_SRC_MULTILEVELBISECTOR_HPP


#include "partition/IBisector.hpp"
#include "aggregation/IAggregator.hpp"
#include "partition/ITwoWayRefiner.hpp"
#include "partition/PartitioningInformation.hpp"
#include "multilevel/IStoppingCriteria.hpp"
#include "util/TimeKeeper.hpp"

#include <memory>

namespace poros
{


class MultilevelBisector : public IBisector
{
  public:
    /**
    * @brief Create a new multilevel bisector.
    *
    * @param aggregator The aggregation scheme to use.
    * @param initialBisector The initial bisector to use.
    * @param refiner The refinement scheme to use.
    */
    MultilevelBisector(
        std::unique_ptr<IAggregator> aggregator,
        std::unique_ptr<IBisector> initialBisector,
        std::unique_ptr<ITwoWayRefiner> refiner,
        std::shared_ptr<TimeKeeper> timeKeeper);


    /**
     * @brief Create a two-way partitioning of the graph.
     *
     * @param target The target partitioning to achieve.
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    virtual Partitioning execute(
        TargetPartitioning const * target,
        Graph const * graph) override;

  protected:
    /**
     * @brief Recurse to a new level.
     *
     * @param level The new level number (counting from 0).
     * @param params The aggregation parameters.
     * @param stoppingCriteria The stopping criteria for coarsening.
     * @param target The target partitioning.
     * @param parent The parent of this graph.
     * @param graph The current graph.
     *
     * @return The partitioning information.
     */
    PartitioningInformation recurse(
        int level,
        AggregationParameters params,
        IStoppingCriteria const * stoppingCriteria,
        TargetPartitioning const * target,
        Graph const * parent,
        Graph const * graph);

  private:
    std::unique_ptr<IAggregator> m_aggregator;
    std::unique_ptr<IBisector> m_initialBisector;
    std::unique_ptr<ITwoWayRefiner> m_refiner;
    std::shared_ptr<TimeKeeper> m_timeKeeper;
};


}


#endif
