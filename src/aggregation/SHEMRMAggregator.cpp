/**
* @file SHEMRMAggregator.cpp
* @brief Implementation of the SHEMRMAggregator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-10
*/

#include "SHEMRMAggregator.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

SHEMRMAggregator::SHEMRMAggregator(
    RandomEngineHandle rng) :
  m_shem(rng),
  m_rm(rng)
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Aggregation SHEMRMAggregator::aggregate(
    AggregationParameters const params,
    Graph const * const graph)
{
  if (graph->hasUniformEdgeWeight()) {
    return m_rm.aggregate(params, graph);
  } else {
    return m_shem.aggregate(params, graph);
  }
}


}

