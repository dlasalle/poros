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

#include <string>
#include <stdexcept>
#include "Base.hpp"

namespace dolos
{


class InvalidBisectionParametersException :
  public std::runtime_error
{
  public:
    InvalidBisectionParametersException(
        std::string msg) :
      runtime_error(msg)
    {
      // do nothing
    }
};


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
    * @param target The target fractions summing to 1.0.
    */
    void setTargetPartitionFractions(
        double const * target);


    /**
     * @brief Set the maximum number of refinement iterations to perform.
     *
     * @param maxIters The maximum number of iterations.
     */
    void setMaxRefinementIterations(
        int const maxIters);


    /**
    * @brief Get the amount of imbalance allowed by these parameters.
    *
    * @return The imbalance fraction.
    */
    double getImbalanceTolerance() const;


    /**
    * @brief Get the vector of the target fractions (will always be of length
    * 2).
    *
    * @return The weight fractions.
    */
    double const * getTargetPartitionFractions() const;


    /**
    * @brief Get the vector of the maximum allowable weight fractions in each
    * partition.
    *
    * @return The weight fractions.
    */
    double const * getMaxPartitionFractions() const;


    /**
     * @brief Get the maximum number of refinement iterations to use.
     *
     * @return The maximum number of iterations.
     */
    int getMaxRefinementIterations() const;


  private:
    double m_imbalanceTolerance;
    double m_targetPartitionFractions[2];
    double m_maxPartitionFractions[2];
    int m_maxRefinementIterations;
};


}

#endif
