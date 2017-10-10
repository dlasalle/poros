/**
* @file BisectionParameters.cpp
* @brief Implementation of the BisectionParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/


#include "BisectionParameters.hpp"
#include "Parameters.hpp"


namespace dolos
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

BisectionParameters::BisectionParameters() :
    m_imbalanceTolerance(0.0),
    m_leftTarget(0.5)
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


void BisectionParameters::setImbalanceTolerance(
    double fraction)
{
  if (fraction < 0.0 || fraction >= 1.0) {
    throw InvalidParametersException(std::string("Invalid imbalance "
        "tolerance ") + std::to_string(fraction) + std::string(". Must be " \
        "equal to or greater than 0.0 and less than 1.0."));
  }

  m_imbalanceTolerance = fraction;
}


void BisectionParameters::setLeftSideTarget(
    double target)
{
  if (target >= 1.0 || target <= 0.0) {
    throw InvalidParametersException(std::string("Invalid target "
        "fraction ") + std::to_string(target) + std::string(". Must be " \
        "greater than 0.0 and less than 1.0."));
  }

  m_leftTarget = target;
}


double BisectionParameters::getImbalanceTolerance() const
{
  return m_imbalanceTolerance;
}

double BisectionParameters::getImbalanceToleranceCoefficient() const
{
  return 1.0 + getImbalanceTolerance();
}


double BisectionParameters::getLeftSideTarget() const
{
  return m_leftTarget;
}


double BisectionParameters::getRightSideTarget() const
{
  return 1.0 - m_leftTarget;
}


double BisectionParameters::getLeftSideMax() const
{
  return getLeftSideTarget() * getImbalanceToleranceCoefficient();
}


double BisectionParameters::getRightSideMax() const
{
  return getRightSideTarget() * getImbalanceToleranceCoefficient();
}


}
