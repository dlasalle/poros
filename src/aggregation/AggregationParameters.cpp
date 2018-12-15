/**
* @file AggregationParameters.cpp
* @brief AggregationParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-23
*/

#include "AggregationParameters.hpp"


namespace poros
{

/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

AggregationParameters::AggregationParameters() :
  m_maxVertexWeight(NULL_WGT)
{
  // do nothing
}

/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void AggregationParameters::setMaxVertexWeight(
    wgt_type const max)
{
  m_maxVertexWeight = max;
}



}
