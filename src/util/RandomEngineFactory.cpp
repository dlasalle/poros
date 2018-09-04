/**
* @file RandomEngineFactory.cpp
* @brief The implementation of the RandomEngineFactory class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-09-04
*/


#include "RandomEngineFactory.hpp"
#include "SimpleRandomEngine.hpp"


namespace dolos
{


/******************************************************************************
* PUBLIC STATIC METHODS *******************************************************
******************************************************************************/

RandomEngineHandle RandomEngineFactory::make(
    unsigned int const seed)
{
  return RandomEngineHandle(new SimpleRandomEngine(seed));
}


}
