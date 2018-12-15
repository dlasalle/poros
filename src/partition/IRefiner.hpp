/**
* @file IRefiner.hpp
* @brief The IRefiner interface.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-09
*/




#ifndef POROS_SRC_IREFINER_HPP
#define POROS_SRC_IREFINER_HPP

#include "Partitioning.hpp"
#include "graph/Graph.hpp"
#include "PartitionParameters.hpp"


namespace poros
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
    * @param params The partition parameters.
    * @param partitioning The partitioning (input and output).
    * @param graph The graph.
    */
    virtual void refine(
        PartitionParameters const * params,
        Partitioning * partitioning,
        Graph const * graph) const = 0;
};


}

#endif
