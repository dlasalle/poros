/**
 * @file IPartitioner.hpp
 * @brief The IPartitioner interface.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */

#ifndef DOLOS_SRC_IPARTITIONER_HPP
#define DOLOS_SRC_IPARTITIONER_HPP


#include "Partitioning.hpp"
#include "ConstantGraph.hpp"

namespace dolos
{

class IPartitioner
{
  public:
    /**
    * @brief Virtual destructor to prevent memory leaks.
    */
    virtual ~IPartitioner() 
    {
      // do nothing
    }

    /**
     * @brief Create a partitioning of the graph.
     *
     * @param params The parameters to use.
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    virtual Partitioning execute(
        Parameters const * params,
        ConstantGraph const * graph) const = 0;

};


}


#endif
