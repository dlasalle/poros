/**
* @file MultilevelBisector.hpp
* @brief The MultilevelBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-09
*/



#ifndef DOLOS_SRC_MULTILEVELBISECTOR_HPP
#define DOLOS_SRC_MULTILEVELBISECTOR_HPP


#include "partition/IBisector.hpp"
#include "aggregation/IAggregator.hpp"
#include "partition/ITwoWayRefiner.hpp"
#include "multilevel/IStoppingCriteria.hpp"
#include "util/TimeKeeper.hpp"

#include <memory>

namespace dolos
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
     * @return The partitioning.
     */
    Partitioning recurse(
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
