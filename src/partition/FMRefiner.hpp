/**
* @file FMRefiner.hpp
* @brief The FMRefiner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-19
*/



#ifndef DOLOS_SRC_FMREFINER_HPP
#define DOLOS_SRC_FMREFINER_HPP


#include "ITwoWayRefiner.hpp"
#include "TargetPartitioning.hpp"


namespace dolos
{

/**
* @brief The refiner implementing the Fidducia-Mattheyses algorithm.
*/
class FMRefiner : public ITwoWayRefiner
{
  public:
    /**
    * @brief Create a new FM refiner.
    *
    * @param maxIters The maximum number of refinement iterations.
    */
    FMRefiner(
        int maxIters); 


    /**
    * @brief Perform FM refinement on the bisection.
    *
    * @param params The parameters of the bisection.
    * @param target The target partitioning.
    * @param connectivity The connectivity.
    * @param partitioning The current partitioning.
    * @param graph The graph.
    */
    void refine(
        TargetPartitioning const * target,
        TwoWayConnectivity * connectivity,
        Partitioning * partitioning,
        ConstantGraph const * graph);

  private:
    int m_maxRefinementIters;

};

}

#endif
