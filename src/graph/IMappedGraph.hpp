/**
 * @file IMappedGraph.hpp
 * @brief The IMappedGraph interface.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-17
 */




#ifndef DOLOS_SRC_IMAPPEDGRAPH_HPP
#define DOLOS_SRC_IMAPPEDGRAPH_HPP


#include "graph/ConstantGraph.hpp"
#include "partition/Partitioning.hpp"

namespace dolos
{


class IMappedGraph
{
  public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~IMappedGraph()
    {
      // do nothing
    }


    /**
     * @brief Get the underyling graph.
     *
     * @return The graph.
     */
    virtual ConstantGraph const * getGraph() const = 0;


    /**
     * @brief Map a sub partitioning of this graph to some other super
     * partitioning.
     *
     * @param subPartitioning The partitioning of this graph.
     * @param partitionLabels The labels to have the mapped partitioning
     * written to.
     * @param offset The offset of partition IDs in the subgraph compared to
     * the super graph.
     */
    virtual void mapPartitioning(
        Partitioning const * subPartitioning,
        pid_type * partitionLabels,
        pid_type offset) const = 0;
};


}

#endif
