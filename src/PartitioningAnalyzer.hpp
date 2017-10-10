/**
* @file PartitioningAnalyzer.hpp
* @brief The PartitioningAnalyzer class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/



#ifndef DOLOS_SRC_PARTITIONINGANALYZER_HPP
#define DOLOS_SRC_PARTITIONINGANALYZER_HPP


#include "Base.hpp"
#include "Partitioning.hpp"
#include "ConstantGraph.hpp"


namespace dolos
{

class PartitioningAnalyzer
{
  public:
    /**
    * @brief Create a new analyzer.
    *
    * @param graph The graph.
    * @param partitioning The partitioning of the graph.
    */
    PartitioningAnalyzer(
        ConstantGraph const * graph,
        Partitioning const * partitioning);


    /**
    * @brief Get the maximum imbalance as a fraction. That is, if a partition
    * is 5% overweight, this function will return 0.05.
    *
    * @return The maximum imbalance.
    */
    double getMaxImbalance() const;
};

}



#endif
