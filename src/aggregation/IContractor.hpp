/**
 * @file IContractor.hpp
 * @brief The IContractor interface.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-01-17
 */




#ifndef DOLOS_SRC_ICONTRACTOR_HPP
#define DOLOS_SRC_ICONTRACTOR_HPP




#include "graph/GraphHandle.hpp"
#include "Aggregation.hpp"
#include "Base.hpp"



namespace dolos
{


class IContractor
{
  public:
    /**
    * @brief The virtual destructor.
    */
    virtual ~IContractor()
    {
      // do nothing
    }


    /**
    * @brief Contract a graph.
    *
    * @param graph The graph to contract.
    * @param aggregation The aggregation specifying which vertices to aggregate
    * together.
    *
    * @return The contracted graph.
    */
    virtual GraphHandle contract(
        Graph const * const graph,
        Aggregation const * const aggregation) = 0;

};




}



#endif
