/**
* @file SummationContractor.hpp
* @brief The SummationContractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-01-17
*/




#ifndef DOLOS_SRC_SUMMATIONCONTRACTOR_HPP
#define DOLOS_SRC_SUMMATIONCONTRACTOR_HPP


#include "aggregation/IContractor.hpp"


namespace dolos
{

class SummationContractor : public IContractor
{
  public:
    /**
    * @brief Create a new summation contractor.
    */
    SummationContractor();


    /**
    * @brief Contract a graph, dropping contracted edge weights, summing
    * combined vertex weights, and summing combined edge weights. 
    *
    * @param graph The graph to contract.
    * @param aggregation The aggregation specifying which vertices to aggregate
    * together.
    *
    * @return The contracted graph.
    */
    GraphHandle contract(
        Graph const * const graph,
        Aggregation const * const aggregation) override;
};




}




#endif
