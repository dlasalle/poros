/**
* @file CompositeStoppingCriteria.cpp
* @brief Implementation of the CompositeStoppingCriteria class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-21
*/

#include "CompositeStoppingCriteria.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

CompositeStoppingCriteria::CompositeStoppingCriteria() :
  m_criteria()
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void CompositeStoppingCriteria::add(
    std::unique_ptr<IStoppingCriteria> criteria)
{
  m_criteria.emplace_back(std::move(criteria));
}

bool CompositeStoppingCriteria::shouldStop(
    int const level,
    Graph const * const fine,
    Graph const * const coarse) const
{
  for (const std::unique_ptr<IStoppingCriteria>& criteria : m_criteria) {
    if (criteria->shouldStop(level, fine, coarse)) {
      return true;
    }
  }

  return false;
}

}
