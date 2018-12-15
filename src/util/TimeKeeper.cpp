/**
 * @file TimeKeeper.cpp
 * @brief Implementation of the TimeKeeper class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-09-25
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */


#include "TimeKeeper.hpp"
#include "solidutils/Debug.hpp"

#include <stdexcept>

namespace poros
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

TimeKeeper::TimeKeeper() :
  m_times(NUM_TIME_CATEGORIES, 0.0),
  m_names{
    "Total",
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
    throw std::runtime_error("Got key " + std::to_string(key) + "/" +
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
