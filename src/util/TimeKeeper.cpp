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

namespace dolos
{

/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void TimeKeeper::addTimeCategory(
    uint32_t const key,
    std::string const name)
{
  if (m_times.size() <= key) {
    m_times.resize(key+1, 0);
    m_names.resize(key+1);
  }

  m_names[key] = name;
}

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
