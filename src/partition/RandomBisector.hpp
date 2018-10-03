/**
 * @file RandomBisector.hpp
 * @brief A class for creating a random bisection.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018
 * @version 1
 * @date 2017-10-04
 */


#ifndef DOLOS_SRC_RANDOMBISECTOR_HPP
#define DOLOS_SRC_RANDOMBISECTOR_HPP


#include "IBisector.hpp"
#include "PartitionParameters.hpp"
#include "util/RandomEngineHandle.hpp"


namespace dolos
{


class RandomBisector :
  public IBisector
{
  public:
    /**
     * @brief Create a new random partitioner with the given parameters.
     *
     * @param randEngine The random engine.
     */
    RandomBisector(
        RandomEngineHandle randEngine);


    /**
    * @brief Deleted copy constructor.
    *
    * @param rhs The bisector to copy.
    */
    RandomBisector(
        RandomBisector const & rhs) = delete;


    /**
    * @brief Deleted assignment operator.
    *
    * @param rhs The bisector to assign.
    */
    RandomBisector operator=(
        RandomBisector const & rhs) = delete;


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
        ConstantGraph const * graph) override;


  private:
  RandomEngineHandle m_randEngine;
};


}


#endif
