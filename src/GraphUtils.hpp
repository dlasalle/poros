/**
* @file GraphUtils.hpp
* @brief The GraphUtils class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/




#ifndef DOLOS_SRC_GRAPHUTILS_HPP
#define DOLOS_SRC_GRAPHUTILS_HPP


#include "ConstantGraph.hpp"
#include "Partitioning.hpp"


namespace dolos
{

class GraphUtils
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
    static std::vector<ConstantGraph> extractParts(
        ConstantGraph const * graph,
        Partitioning const * part);
};


}


#endif
