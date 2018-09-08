/**
* @file DolosParameters.cpp
* @brief Implementation of the DolosParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-26
*/


#include "DolosParameters.hpp"
#include "util/RandomEngineFactory.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

DolosParameters::DolosParameters(
    dolos_options_struct const options) :
  m_randomEngine(RandomEngineFactory::make(options.randomSeed)),
  m_aggregationScheme(options.aggregationScheme)
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

RandomEngineHandle DolosParameters::randomEngine()
{
  return m_randomEngine;
}

int DolosParameters::aggregationScheme() const
{
  return m_aggregationScheme;
}


}
