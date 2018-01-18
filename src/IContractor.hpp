/**
 * @file IContractor.hpp
 * @brief The IContractor interface.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018, Solid Lake LLC
 * @version 1
 * @date 2018-01-17
 */




#ifndef DOLOS_SRC_ICONTRACTOR_HPP
#define DOLOS_SRC_ICONTRACTOR_HPP




#include "ConstantGraph.hpp"
#include "Base.hpp"



namespace dolos
{


class IContractor
{
  public:
    /**
    * @brief The virtual destructor.
    */
    virtual ~IContractor(); 


    /**
    * @brief Contract a graph.
    *
    * @param graph The graph to contract.
    * @param aggregation The aggregation specifying which vertices to aggregate
    * together.
    *
    * @return The contracted graph.
    */
    virtual ConstantGraph contract(
        ConstantGraph const * const graph,
        Aggregation const * const aggregation) = 0;

};




}



#endif
