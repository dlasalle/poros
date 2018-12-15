/**
* @file PorosParameters.cpp
* @brief Implementation of the PorosParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-26
*/


#include "PorosParameters.hpp"
#include "util/RandomEngineFactory.hpp"


namespace poros
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

PorosParameters::PorosParameters(
    poros_options_struct const options) :
  m_randomEngine(RandomEngineFactory::make(options.randomSeed)),
  m_aggregationScheme(options.aggregationScheme)
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

RandomEngineHandle PorosParameters::randomEngine()
{
  return m_randomEngine;
}

int PorosParameters::aggregationScheme() const
{
  return m_aggregationScheme;
}


}
