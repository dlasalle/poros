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
        std::unique_ptr<ITwoWayRefiner> refiner);


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
        ConstantGraph const * graph) override;

  protected:
    /**
     * @brief Recurse to a new level.
     *
     * @param level The new level number (counting from 0).
     * @param target The target partitioning.
     * @param graph The current graph.
     *
     * @return The partitioning.
     */
    Partitioning recurse(
        int level,
        IStoppingCriteria const * stoppingCriteria,
        TargetPartitioning const * target,
        ConstantGraph const * parent,
        ConstantGraph const * graph);

  private:
    std::unique_ptr<IAggregator> m_aggregator;
    std::unique_ptr<IBisector> m_initialBisector;
    std::unique_ptr<ITwoWayRefiner> m_refiner;

};

}


#endif
