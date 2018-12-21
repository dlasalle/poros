/**
* @file EdgeRatioStoppingCriteria.cpp
* @brief Implementation of the EdgeRatioStoppingCriteria class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-20
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/


#include "EdgeRatioStoppingCriteria.hpp"

#include <stdexcept>
#include <string>


namespace poros
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

EdgeRatioStoppingCriteria::EdgeRatioStoppingCriteria(
    double ratio) :
  m_ratio(ratio)
{
  if (ratio <= 0.0 || ratio >= 1.0) {
    throw std::runtime_error("Stopping criteria for edge ratio must be "
        "in the range (0.0, 1.0): " + std::to_string(ratio));
  }
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

bool EdgeRatioStoppingCriteria::shouldStop(
    int const level,
    Graph const * const fine,
    Graph const * const coarse) const
{
  if (level > 0 && fine == nullptr) {
    throw std::runtime_error("Cannot evaluate stopping condition on "
        "level greater than 0 with a null fine graph.");
  } else if (coarse == nullptr) {
    throw std::runtime_error("Coarse graph for stopping condition "
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
    return ratio > m_ratio;
  }
}


}
