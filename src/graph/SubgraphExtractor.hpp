/**
* @file SubgraphExtractor.hpp
* @brief The SubgraphExtractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-10
*/




#ifndef DOLOS_SRC_SUBGRAPHEXTRACTOR_HPP
#define DOLOS_SRC_SUBGRAPHEXTRACTOR_HPP


#include "graph/Graph.hpp"
#include "partition/Partitioning.hpp"
#include "graph/Subgraph.hpp"


namespace dolos
{

class SubgraphExtractor
{
  public:
    /**
    * @brief Extract the subgraph formed by each partition.
    *
    * @param graph The graph.
    * @param part The partitioning.
    * @param labels The labels of the vertices in the graph (may be null if
    * they are not aliased).
    *
    * @return The subgraphs.
    */
    static std::vector<Subgraph> partitions(
        Graph const * graph,
        Partitioning const * part,
        vtx_type const * const labels = nullptr);
};


}


#endif
