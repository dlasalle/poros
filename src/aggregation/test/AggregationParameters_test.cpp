/**
* @file AggregationParameters_test.cpp
* @brief Unit tests for the AggregationParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-23
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
