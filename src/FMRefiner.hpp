/**
* @file FMRefiner.hpp
* @brief The FMRefiner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-19
*/



#ifndef DOLOS_SRC_FMREFINER_HPP
#define DOLOS_SRC_FMREFINER_HPP


#include "ITwoWayRefiner.hpp"


namespace dolos
{

/**
* @brief The refiner implementing the Fidducia-Mattheyses algorithm.
*/
class FMRefiner
{
  public:
    /**
    * @brief Create a new FM refiner.
    */
    FMRefiner(); 


    /**
    * @brief Perform FM refinement on the bisection.
    *
    * @param params The parameters of the bisection.
    * @param connectivity The connectivity.
    * @param graph The graph.
    */
    void refine(
        BisectionParameters const * params,
        TwoWayConnectivity * connectivity,
        ConstantGraph const * graph) const;
};

}

#endif
