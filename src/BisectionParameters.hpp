/**
* @file BisectionParameters.hpp
* @brief The BisectionParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/




#ifndef DOLOS_SRC_BISECTIONPARAMETERS_HPP
#define DOLOS_SRC_BISECTIONPARAMETERS_HPP

#include "Base.hpp"

namespace dolos
{

class BisectionParameters
{
  public:
    /**
    * @brief Create a default set of parameters for bisectioning a graph.
    */
    BisectionParameters();


    /**
    * @brief Set the amount of imbalance to allow as a fraction (0.03 = 3%).
    *
    * @param toleranceFraction The amount of imbalance to allow.
    */
    void setImbalanceTolerance(
        double toleranceFraction);


    /**
    * @brief Set the target fraction of weight to place in the left/0th
    * partiion.
    *
    * @param target The target fraction between 0 and 1.0.
    */
    void setLeftSideTarget(
        double target);


    /**
    * @brief Get the amount of imbalance allowed by these parameters.
    *
    * @return The imbalance fraction.
    */
    double getImbalanceTolerance() const;


    /**
    * @brief Get the imbalance tolerance as a coefficient (e.g., 3% is 1.03).
    *
    * @return The coefficient.
    */
    double getImbalanceToleranceCoefficient() const;


    /**
    * @brief Get the target weight fraction of the left/0th partition. 
    *
    * @return The target fraction.
    */
    double getLeftSideTarget() const;


    /**
    * @brief Get the target weight fraction of the left/0th partition. 
    *
    * @return The target fraction.
    */
    double getRightSideTarget() const;


    /**
    * @brief Get the maximum fraction of the weight allowable on the left/0th
    * partition.
    *
    * @return The maximum fraction.
    */
    double getLeftSideMax() const;


    /**
    * @brief Get the maximum fraction of the weight allowable on the right/1th
    * partition.
    *
    * @return The maximum fraction.
    */
    double getRightSideMax() const;


  private:
    double m_imbalanceTolerance;
    double m_leftTarget;
};


}

#endif
