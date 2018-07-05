/**
* @file BFSBisector.hpp
* @brief The BFSBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-04
*/


#ifndef DOLOS_SRC_BFSBISECTOR_HPP
#define DOLOS_SRC_BFSBISECTOR_HPP

#include "IBesctor.hpp"

namespace dolos
{

class BFSBisector
{
  public:
    /**
    * @brief Create a new BFSBisector.
    *
    * @param rng The random engine to use.
    */
    BFSBisector(
        IRandomEngine * rng);

    /**
     * @brief Create a two-way partitioning of the graph via weighted BFS.
     *
     * @param target The target partitioning to achieve.
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    virtual Partitioning execute(
        TargetPartitioning const * target,
        ConstantGraph const * graph) const override;



};

}


#endif
