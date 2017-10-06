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


namespace dolos
{


class RecursiveBisectionPartitioner :
  public IPartitioner
{
  public:
    /**
    * @brief Create a new recursive bisection partitioner given the parameters.
    *
    * @param params The parameters to use.
    */
    RecursiveBisectionPartitioner(
        Parameters const * params);


    /**
     * @brief Create a partitioning of the graph.
     *
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    virtual Partitioning execute(
        ConstantGraph const * graph) const override;



};


}


#endif
