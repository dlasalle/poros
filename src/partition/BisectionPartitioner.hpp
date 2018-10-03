/**
* @file BisectionPartitioner.hpp
* @brief The BisectionPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-11-08
*/



#ifndef DOLOS_SRC_BISECTIONPARTITIONER_HPP
#define DOLOS_SRC_BISECTIONPARTITIONER_HPP


#include "IPartitioner.hpp"
#include "IBisector.hpp"

namespace dolos
{


class BisectionPartitioner :
    public IBisector
{
  public:
    /**
    * @brief Create a new adapter to treat the partitioner as a bisector.
    *
    * @param partitioner The partitioner.
    */
    BisectionPartitioner(
        IPartitioner * partitioner);


    /**
    * @brief Virtual destructor.
    */
    virtual ~BisectionPartitioner();


    /**
     * @brief Create a two-way partitioning of the graph.
     *
     * @param target The target partitioning to achieve.
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     *
     * @throws If the target has a number of partitions that is not two, an
     * sl::InvalidInputException is thrown.
     */
    virtual Partitioning execute(
        TargetPartitioning const * target,
        ConstantGraph const * graph);


  private:
    IPartitioner * m_partitioner;

    // disable copying
    BisectionPartitioner(
        BisectionPartitioner const & lhs);
    BisectionPartitioner & operator=(
        BisectionPartitioner const & lhs);
};

}


#endif
