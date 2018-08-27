/**
* @file SimpleRandomEngine.cpp
* @brief Implementation of the SimpleRandomEngine class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-20
*/


#include "SimpleRandomEngine.hpp"
#include <algorithm>

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

SimpleRandomEngine::SimpleRandomEngine(
    unsigned int const seed) : m_rng(seed)
{
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void SimpleRandomEngine::fillWithPerm(
    vtx_type * container,
    vtx_type const start,
    vtx_type const end)
{
  for (vtx_type i = 0; i < end-start; ++i) {
    container[i] = start + i;
  }

  std::shuffle(container + start, container + end, m_rng);
}


vtx_type SimpleRandomEngine::randInRange(
    vtx_type const min,
    vtx_type const max)
{
  return std::uniform_int_distribution<vtx_type>(min, max)(m_rng);
}


void SimpleRandomEngine::setSeed(
    unsigned int const seed)
{
  // reset the seed
  m_rng = std::mt19937(seed);
}

}
