/**
 * @file IBisector.hpp
 * @brief The Bisector interface.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018
 * @version 1
 * @date 2017-10-04
 */

#ifndef DOLOS_SRC_IBISECTOR_HPP
#define DOLOS_SRC_IBISECTOR_HPP


#include "graph/Graph.hpp"
#include "Partitioning.hpp"
#include "TargetPartitioning.hpp"


namespace dolos
{

class IBisector
{
  public:
    /**
    * @brief Virtual destructor to prevent memory leaks.
    */
    virtual ~IBisector() 
    {
      // do nothing
    }


    /**
     * @brief Create a two-way partitioning of the graph.
     *
     * @param target The target partitioning to achieve.
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    virtual Partitioning execute(
        TargetPartitioning const * target,
        Graph const * graph) = 0;


};


}


#endif
