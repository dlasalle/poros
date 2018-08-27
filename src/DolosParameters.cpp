/**
* @file DolosParameters.cpp
* @brief Implementation of the DolosParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-26
*/


#include "DolosParameters.hpp"
#include "util/SimpleRandomEngine.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

DolosParameters::DolosParameters(
    dolos_options_struct const * options) :
  m_randomEngine(new SimpleRandomEngine())
{
  if (options != nullptr) {
    m_randomEngine.setSeed(options->randomSeed);
  }
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

RandomEngineHandle DolosParameters::randomEngine()
{
  return m_randomEngine;
}



}
