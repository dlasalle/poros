/**
* @file PureBalanceRefiner.hpp
* @brief The PureBalanceRefiner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-18
*/



#ifndef DOLOS_SRC_PUREBALANCEREFINER_HPP
#define DOLOS_SRC_PUREBALANCEREFINER_HPP

#include "ITwoWayRefiner.hpp"

namespace dolos
{

/**
* @brief A 2-way refinement method which does not take connectivity into
* account, but ensure balance where possible.
*/
class PureBalanceRefiner :
    public ITwoWayRefiner
{
  public:
    /**
    * @brief Create a new two way balance refiner.
    */
    PureBalanceRefiner();


    /**
    * @brief Refine the partition for the given graph.
    *
    * @param params The parameters of the bisection.
    * @param partitioning The partitioning (input and output).
    * @param graph The graph.
    */
    void refine(
        BisectionParameters const * params,
        Partitioning * partitioning,
        ConstantGraph const * graph) const;
};


}

#endif
