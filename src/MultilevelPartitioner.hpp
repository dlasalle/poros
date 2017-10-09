/**
 * @file MultilevelPartitioner.hpp
 * @brief The MultilevelPartitioner class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#ifndef DOLOS_SRC_MULTILEVELPARTITIONER_HPP
#define DOLOS_SRC_MULTILEVELPARTITIONER_HPP


#include "IPartitioner.hpp"
#include "IAggregator.hpp"
#include "IRefiner.hpp"


namespace dolos
{


class MultilevelPartitioner
{
  public:
    /**
    * @brief Create a new mutilevel partitioner. 
    *
    * @param aggregator The aggregation algorithm to use.
    * @param initiailPartitioner The initial partitioning algorithm to use.
    * @param refiner The refinement algorithm to use.
    */
    MultilevelPartitioner(
        IAggregator const * aggregator,
        IPartitioner const * initiailPartitioner,
        IRefiner const * refiner);


    /**
     * @brief Create a partitioning of the graph.
     *
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    virtual Partitioning execute(
        ConstantGraph const * graph) const;


     
};

}

#endif
