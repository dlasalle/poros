/**
* @file AggregationParameters.hpp
* @brief The AggregationParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-23
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



#ifndef POROS_SRC_AGGREGATIONPARAMETERS_HPP
#define POROS_SRC_AGGREGATIONPARAMETERS_HPP

#include "Base.hpp"

namespace poros
{

class AggregationParameters
{
  public:
    /**
    * @brief Create a new set of aggregation parameters.
    */
    AggregationParameters();

    /**
    * @brief Set the maximum weight of a vertex allowed.
    *
    * @param max The maximum weight.
    */
    void setMaxVertexWeight(
        wgt_type max);

    /**
    * @brief Check if a vertex weight would be acceptable.
    *
    * @param wgt The weight of the proposed vertex.
    *
    * @return True if the weight is within allowed limits.
    */
    inline bool isAllowedVertexWeight(
        wgt_type wgt) const
    {
      // if m_maxVertexWeight has not been set, everything is allowed.
      return wgt == NULL_WGT || wgt <= m_maxVertexWeight;
    }

  private:
  wgt_type m_maxVertexWeight;

};

}

#endif
