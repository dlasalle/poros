/**
* @file SubgraphExtractor.hpp
* @brief The SubgraphExtractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/




#ifndef DOLOS_SRC_SUBGRAPHEXTRACTOR_HPP
#define DOLOS_SRC_SUBGRAPHEXTRACTOR_HPP


#include "ConstantGraph.hpp"
#include "Partitioning.hpp"
#include "Subgraph.hpp"


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
    *
    * @return The subgraphs.
    */
    static std::vector<Subgraph> partitions(
        ConstantGraph const * graph,
        Partitioning const * part);
};


}


#endif
