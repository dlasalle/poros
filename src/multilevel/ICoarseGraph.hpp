/**
* @file ICoarseGraph.hpp
* @brief The ICoarseGraph interface.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-10
*/


#ifndef DOLOS_SRC_MULTILEVEL_ICOARSEGRAPH_HPP
#define DOLOS_SRC_MULTILEVEL_ICOARSEGRAPH_HPP


#include "graph/GraphHandle.hpp"
#include "partition/Partitioning.hpp"
#include "partition/PartitioningInformation.hpp"

namespace dolos
{


class ICoarseGraph
{
  public:
  /**
  * @brief Virtual destructor.
  */
  virtual ~ICoarseGraph()
  {
    // do nothing
  }


  /**
  * @brief Get the coarsened graph.
  *
  * @return The coarsened graph.
  */
  virtual Graph const * graph() const = 0;


  /**
  * @brief Project the partitioning of the coarse graph to the fine graph.
  *
  * @param coarseInfo The partitioning information of the coarse graph.
  *
  * @return The partitioning information of the fine graph.
  */
  virtual PartitioningInformation project(
      PartitioningInformation const * coarseInfo) = 0;



};


}

#endif
