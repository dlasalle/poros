/**
* @file ITwoWayRefiner.hpp
* @brief The ITwoWayRefiner interface.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-18
*/



#ifndef DOLOS_SRC_ITWOWAYREFINER_HPP
#define DOLOS_SRC_ITWOWAYREFINER_HPP


#include "TargetPartitioning.hpp"
#include "Partitioning.hpp"
#include "TwoWayConnectivity.hpp"
#include "graph/ConstantGraph.hpp"


namespace dolos
{

class ITwoWayRefiner
{
  public:
    /**
    * @brief Virtual destructor to prevent memory leaks.
    */
    virtual ~ITwoWayRefiner()
    {
      // do nothing
    }


    /**
    * @brief Refine the partition for the given graph.
    *
    * @param params The parameters of the bisection.
    * @param partitioning The partitioning (input and output).
    * @param connectivity The connectivity of vertices to the partitions.
    * @param graph The graph.
    */
    virtual void refine(
        TargetPartitioning const * target,
        TwoWayConnectivity * connectivity,
        Partitioning * partitioning,
        ConstantGraph const * graph) = 0;
};


}




#endif
