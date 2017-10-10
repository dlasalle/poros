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
#include "BisectionParameters.hpp"

namespace dolos
{

namespace
{

pid_type const LEFT_PARTITION = 0;
pid_type const RIGHT_PARTITION = 1;
pid_type const NUM_BISECTION_PARTS = 2;

}

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
     * @param parameters The bisection parameters.
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    virtual Partitioning execute(
        BisectionParameters const * parameters,
        ConstantGraph const * graph) const = 0;

};


}


#endif
