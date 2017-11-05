/**
* @file RecursiveBisectionPartitioner.hpp
* @brief The RecursiveBisectionPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-06
*/



#ifndef DOLOS_SRC_RECURSIVEBISECTIONPARTITIONER_HPP
#define DOLOS_SRC_RECURSIVEBISECTIONPARTITIONER_HPP


#include "IPartitioner.hpp"
#include "IBisector.hpp"
#include "IMappedGraph.hpp"


namespace dolos
{


class RecursiveBisectionPartitioner :
  public IPartitioner
{
  public:
    /**
    * @brief Create a new recursive bisection partitioner given the parameters.
    *
    * @param params The parameters to use when partitioning.
    * @param bisector The bisector to use.
    */
    RecursiveBisectionPartitioner(
        IBisector const * bisector);


    /**
     * @brief Create a partitioning of the graph.
     *
     * @param target The target partitioning to achieve.
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    Partitioning execute(
        TargetPartitioning const * target,
        ConstantGraph const * graph) const override;


  private:
    IBisector const * m_bisector;


    /**
     * @brief Recursively execute on a subgraph.
     *
     * @param partitionLabels The partitioning to populate.
     * @param target The target partitioning to achieve.
     * @param subGraph The subgraph to recursively partition.
     * @param offset The partition ID offset to assign.
     */
    void recurse(
        pid_type * partitionLabels,
        TargetPartitioning const * target,
        IMappedGraph const * subGraph,
        pid_type const offset) const;


    // disable copying
    RecursiveBisectionPartitioner(
        RecursiveBisectionPartitioner const & lhs);
    RecursiveBisectionPartitioner & operator=(
        RecursiveBisectionPartitioner const & lhs);

};


}


#endif
