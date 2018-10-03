/**
 * @file TimeKeeper.cpp
 * @brief Implementation of the TimeKeeper class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-09-25
 */


#include "TimeKeeper.hpp"

#include "solidutils/Exception.hpp"
#include "solidutils/Debug.hpp"

namespace dolos
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

TimeKeeper::TimeKeeper() :
  m_times(NUM_TIME_CATEGORIES, 0.0),
  m_names{
    "Coarsening",
    "Aggregation",
    "Contraction",
    "Initial Partitioning",
    "Uncoarsening",
    "Refinement",
    "Projection"
  }
{
  ASSERT_EQUAL(m_times.size(), m_names.size());
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void TimeKeeper::reportTime(
    uint32_t const key,
    double const seconds)
{
  if (key >= m_times.size()) {
    throw sl::InvalidInputException("Got key " + std::to_string(key) + "/" +
        std::to_string(m_times.size()));
  }

  m_times[key] += seconds;
}

std::vector<std::pair<std::string, double>> TimeKeeper::times() const
{
  std::vector<std::pair<std::string, double>> data;
  data.reserve(m_times.size());

  for (size_t i = 0; i < m_times.size(); ++i) {
    data.emplace_back(m_names[i], m_times[i]);
  }

  return data;
}




}
