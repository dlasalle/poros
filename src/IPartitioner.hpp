/**
 * @file IPartitioner.hpp
 * @brief The Partitioner interface.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#include "Partitioning.hpp"

namespace dolos
{

class IPartitioner
{
  public:
    virtual ~Partitioner() 
    {
      // do nothing
    }

    /**
     * @brief Create a partitioning of the graph.
     *
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    virtual Partitioning execute(
        Graph const * graph) const = 0;

}


}
