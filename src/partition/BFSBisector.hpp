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

#include "IBisector.hpp"
#include "util/IRandomEngine.hpp"

namespace dolos
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
        IRandomEngine * rng);

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
        ConstantGraph const * graph) override;


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
        ConstantGraph const * graph,
        vtx_type seedVertex);

  private:
    IRandomEngine * m_rng;

};

}


#endif