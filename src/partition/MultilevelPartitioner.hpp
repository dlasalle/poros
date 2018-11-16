/**
 * @file MultilevelPartitioner.hpp
 * @brief The MultilevelPartitioner class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018
 * @version 1
 * @date 2017-10-04
 */


#ifndef DOLOS_SRC_MULTILEVELPARTITIONER_HPP
#define DOLOS_SRC_MULTILEVELPARTITIONER_HPP


#include "partition/IPartitioner.hpp"
#include "partition/IRefiner.hpp"
#include "aggregation/IAggregator.hpp"

#include <memory>

namespace dolos
{


class MultilevelPartitioner :
    public IPartitioner
{
  public:
    /**
    * @brief Create a new mutilevel partitioner. 
    *
    * @param aggregator The aggregation algorithm to use.
    * @param initialPartitioner The initial partitioning algorithm to use.
    * @param refiner The refinement algorithm to use.
    */
    MultilevelPartitioner(
        std::unique_ptr<IAggregator> aggregator,
        std::unique_ptr<IPartitioner> initialPartitioner,
        std::unique_ptr<IRefiner> refiner);

    /**
     * @brief Create a partitioning of the graph.
     *
     * @param target The target partitioning to achieve.
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    virtual Partitioning execute(
        TargetPartitioning const * target,
        Graph const * graph) override;

  private:
    std::unique_ptr<IAggregator> m_aggregator;
    std::unique_ptr<IPartitioner> m_initialPartitioner;
    std::unique_ptr<IRefiner> m_refiner;
     
};

}

#endif
