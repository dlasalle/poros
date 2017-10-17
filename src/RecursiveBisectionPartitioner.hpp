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


namespace dolos
{


class RecursiveBisectionPartitioner :
  public IPartitioner
{
  public:
    /**
    * @brief Create a new recursive bisection partitioner given the parameters.
    *
    * @param bisector The bisector to use.
    */
    RecursiveBisectionPartitioner(
        IBisector const * bisector);


    /**
     * @brief Create a partitioning of the graph.
     *
     * @param params The parameters to use.
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    Partitioning execute(
        PartitionParameters const * params,
        ConstantGraph const * graph) const override;


  private:
    IBisector const * m_bisector;

    /**
     * @brief Recursively execute on a subgraph.
     *
     * @param superPartitioning The partitioning to populate.
     * @param params THe parameters to use.
     * @param subGraph The subgraph to recursively partition.
     * @param offset The partition ID offset to assign.
     */
    recurse(
        Partitioning * const superPartitioning,
        PartitionParameters const * const params,
        Subgraph const * subGraph,
        pid_type const offset) const;


    // disable copying
    RecursiveBisectionPartitioner(
        RecursiveBisectionPartitioner const & lhs);
    RecursiveBisectionPartitioner & operator=(
        RecursiveBisectionPartitioner const & lhs);

};


}


#endif
