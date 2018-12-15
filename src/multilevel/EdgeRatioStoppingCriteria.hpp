/**
* @file EdgeRatioStoppingCriteria.hpp
* @brief The EdgeRatioStoppingCriteria class.
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


#ifndef POROS_SRC_EDGERATIOSTOPPINGCRITERIA_HPP
#define POROS_SRC_EDGERATIOSTOPPINGCRITERIA_HPP

#include "graph/Graph.hpp"
#include "multilevel/IStoppingCriteria.hpp"

namespace poros
{

class EdgeRatioStoppingCriteria : public IStoppingCriteria
{
  public:
  /**
  * @brief Create a new EdgeRatioStoppingCriteria.
  *
  * @param ratio The ratio at which to stop coarsening.
  */
  EdgeRatioStoppingCriteria(
      double ratio);

  /**
  * @brief Determine if coarsening should terminate based on the ratio of the
  * fine and coarse graphs.
  *
  * @param level The level of the coarsest graph.
  * @param fine The fine graph (previous -- may be nullptr).
  * @param coarse The coarse graph (next).
  *
  * @return True if coarseing should stop at the coarse graph.
  */
  bool shouldStop(
      int level,
      Graph const * fine,
      Graph const * coarse) const override;


  private:
  double m_ratio;
};




}

#endif
