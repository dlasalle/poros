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


#include "Partitioning.hpp"
#include "ConstantGraph.hpp"
#include "BisectionParameters.hpp"
#include "TwoWayConnectivity.hpp"


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
    * @param graph The graph.
    */
    virtual void refine(
        BisectionParameters const * params,
        Partitioning * partitioning,
        ConstantGraph const * graph) const = 0;
};


}




#endif
