/**
 * @file RandomBisector.hpp
 * @brief A class for creating a random bisection.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#ifndef DOLOS_SRC_RANDOMBISECTOR_HPP
#define DOLOS_SRC_RANDOMBISECTOR_HPP


#include "IBisector.hpp"
#include "PartitionParameters.hpp"


namespace dolos
{


class RandomBisector :
  public IBisector
{
  public:
    /**
     * @brief Create a new random partitioner with the given parameters.
     */
    RandomBisector();


    /**
     * @brief Destructor.
     */
    virtual ~RandomBisector();


    /**
     * @brief Randomly assign vertices to partitions.
     *
     * @param target The target partitioning to achieve.
     * @param graph The graph.
     *
     * @return The assigned partitioning.
     */
    virtual Partitioning execute(
        TargetPartitioning const * target,
        ConstantGraph const * graph) const override;


};


}


#endif
