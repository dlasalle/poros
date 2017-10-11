/**
* @file BisectionParameters.cpp
* @brief Implementation of the BisectionParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/


#include "BisectionParameters.hpp"

#include <string>

namespace dolos
{

namespace
{

double const FRACTION_SUM_TOLERANCE = 0.0001;
double const MIN_FRACTION_SUM = 1.0 - FRACTION_SUM_TOLERANCE;
double const MAX_FRACTION_SUM = 1.0 + FRACTION_SUM_TOLERANCE;

}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

BisectionParameters::BisectionParameters() :
    m_imbalanceTolerance(0.0),
    m_targetPartitionFractions{0.5, 0.5},
    m_maxPartitionFractions{0.5, 0.5}
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


void BisectionParameters::setImbalanceTolerance(
    double const fraction)
{
  if (fraction < 0.0 || fraction >= 1.0) {
    throw InvalidBisectionParametersException(std::string("Invalid " \
        "imbalance tolerance ") + std::to_string(fraction) + std::string( \
        ". Must be equal to or greater than 0.0 and less than 1.0."));
  }

  m_imbalanceTolerance = fraction;

  double const coeff = 1.0 + fraction;
  
  // update maximums
  m_maxPartitionFractions[0] = m_targetPartitionFractions[0] * coeff; 
  m_maxPartitionFractions[1] = m_targetPartitionFractions[1] * coeff; 
}


void BisectionParameters::setTargetPartitionFractions(
    double const * const target)
{
  if (target[0] + target[1] >= MAX_FRACTION_SUM || \
      target[0] + target[1] <= MIN_FRACTION_SUM) {
    throw InvalidBisectionParametersException(std::string("Invalid target " \
        "fractions {") + std::to_string(target[0]) + std::string(", ") + \
        std::to_string(target[1]) + std::string("} . Must sum to 1.0."));
  }

  // update targets
  m_targetPartitionFractions[0] = target[0];
  m_targetPartitionFractions[1] = target[1];

  // implicitly update maximums
  setImbalanceTolerance(getImbalanceTolerance());
}


double BisectionParameters::getImbalanceTolerance() const
{
  return m_imbalanceTolerance;
}

double const * BisectionParameters::getTargetPartitionFractions() const
{
  return m_targetPartitionFractions;
}


double const * BisectionParameters::getMaxPartitionFractions() const
{
  return m_maxPartitionFractions;
}


}
