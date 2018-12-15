/**
* @file SimpleRandomEngine.cpp
* @brief Implementation of the SimpleRandomEngine class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-20
*/


#include "SimpleRandomEngine.hpp"
#include "solidutils/Random.hpp"


namespace poros
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

SimpleRandomEngine::SimpleRandomEngine(
    unsigned int const seed) : m_rng(seed)
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void SimpleRandomEngine::fillWithPerm(
    vtx_type * container,
    vtx_type const start,
    vtx_type const end)
{
  sl::Random::fillWithPerm(container, end-start, start, m_rng);
}


void SimpleRandomEngine::setSeed(
    unsigned int const seed)
{
  // reset the seed
  m_rng = std::mt19937(seed);
}


}
