/**
* @file AggregationParameters_test.cpp
* @brief Unit tests for the AggregationParameters class.
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


#include "aggregation/AggregationParameters.hpp"

#include "solidutils/UnitTest.hpp"


namespace poros
{

UNITTEST(AggregationParameters, MaxVertexWeightTest)
{
  AggregationParameters params;

  testTrue(params.isAllowedVertexWeight(1U));
  testTrue(params.isAllowedVertexWeight(10U));
  testTrue(params.isAllowedVertexWeight(100U));
  testTrue(params.isAllowedVertexWeight(1000U));
  testTrue(params.isAllowedVertexWeight(10000U));
  testTrue(params.isAllowedVertexWeight(100000U));

  params.setMaxVertexWeight(15U);

  testTrue(params.isAllowedVertexWeight(1U));
  testTrue(params.isAllowedVertexWeight(10U));
  testTrue(params.isAllowedVertexWeight(15U));
  testFalse(params.isAllowedVertexWeight(16U));
  testFalse(params.isAllowedVertexWeight(1000U));
}

}
