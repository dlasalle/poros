/**
* @file EdgeRatioStoppingCriteria.cpp
* @brief Implementation of the EdgeRatioStoppingCriteria class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-20
*/


#include "EdgeRatioStoppingCriteria.hpp"
#include "solidutils/Exception.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

EdgeRatioStoppingCriteria::EdgeRatioStoppingCriteria(
    double ratio) :
  m_ratio(ratio)
{
  if (ratio <= 0.0 || ratio >= 1.0) {
    throw sl::InvalidInputException("Stopping criteria for edge ratio must be "
        "in the range (0.0, 1.0): " + std::to_string(ratio));
  }
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

bool EdgeRatioStoppingCriteria::shouldStop(
    int const level,
    ConstantGraph const * const fine,
    ConstantGraph const * const coarse) const
{
  if (level > 0 && fine == nullptr) {
    throw sl::InvalidInputException("Cannot evaluate stopping condition on "
        "level greater than 0 with a null fine graph.");
  } else if (coarse == nullptr) {
    throw sl::InvalidInputException("Coarse graph for stopping condition "
        "cannot be null.");
  }

  if (coarse->numEdges() == 0) {
    // always stop if we run out of edges
    return true;
  } else if (fine == nullptr) {
    // if we're at the first level and we have edges, don't stop
    return false;
  } else if (fine->numEdges() == 0) {
    // if our fine graph has no edges, just stop
    return true;
  } else {
    // stop based on the ratio
    double const ratio = static_cast<double>(coarse->numEdges()) / \
                         static_cast<double>(fine->numEdges());

    // if our ratio is greater, then we stop (e.g., we have 97% the number of
    // eges in the coarse graph as in the fine, and the stopping condition is
    // 95%
    return ratio < m_ratio;
  }
}


}
