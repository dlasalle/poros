/**
 * @file IBisector.hpp
 * @brief The Bisector interface.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */

#ifndef DOLOS_SRC_IBISECTOR_HPP
#define DOLOS_SRC_IBISECTOR_HPP


#include "Partitioning.hpp"
#include "ConstantGraph.hpp"

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
     * @brief Create a partitioning of the graph.
     *
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    virtual Partitioning execute(
        ConstantGraph const * graph) const = 0;

};


}


#endif
