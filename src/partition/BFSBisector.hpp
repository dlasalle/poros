/**
* @file BFSBisector.hpp
* @brief The BFSBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-04
*/


#ifndef POROS_SRC_BFSBISECTOR_HPP
#define POROS_SRC_BFSBISECTOR_HPP

#include "IBisector.hpp"
#include "util/RandomEngineHandle.hpp"

namespace poros
{

class BFSBisector : public IBisector
{
  public:
    /**
    * @brief Create a new BFSBisector.
    *
    * @param rng The random engine to use.
    */
    BFSBisector(
        RandomEngineHandle rng);

    /**
    * @brief Deleted copy constructor.
    *
    * @param rhs The bisector to copy.
    */
    BFSBisector(
        BFSBisector const & rhs) = delete;

    /**
    * @brief Deleted assignment operator.
    *
    * @param rhs The bisector to assign from.
    *
    * @return This bisector.
    */
    BFSBisector& operator=(
        BFSBisector const & rhs) = delete;

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
        Graph const * graph) override;


    /**
    * @brief Create a two-way partitioning of the graph via weighted BFS with
    * the given seed vertex.
    *
    * @param target The taget partitioning.
    * @param graph The graph.
    * @param seedVertex The seed vertex.
    *
    * @return The partitioning.
    */
    virtual Partitioning execute(
        TargetPartitioning const * target,
        Graph const * graph,
        Vertex const seedVertex);

  private:
    RandomEngineHandle m_rng;

};

}


#endif
