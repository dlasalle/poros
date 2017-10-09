/**
* @file IRefiner.hpp
* @brief The IRefiner interface.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/




#ifndef DOLOS_SRC_IREFINER_HPP
#define DOLOS_SRC_IREFINER_HPP

#include "Partitioning.hpp"
#include "ConstantGraph.hpp"


namespace dolos
{

class IRefiner
{
  public:
    /**
    * @brief Virtual destructor to prevent memory leaks.
    */
    virtual ~IRefiner()
    {
      // do nothing
    }


    /**
    * @brief Refine the partition for the given graph.
    *
    * @param partitioning The partitioning (input and output).
    * @param graph The graph.
    */
    virtual void refine(
        Partitioning * partitioning,
        ConstantGraph const * graph) const = 0;
};


}

#endif
