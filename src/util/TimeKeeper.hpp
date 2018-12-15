/**
 * @file TimeKeeper.h
 * @brief The TimeKeeper class.
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


#ifndef POROS_SRC_UTIL_TIMEKEEPER_HPP
#define POROS_SRC_UTIL_TIMEKEEPER_HPP

#include <cstdint>
#include <vector>
#include <utility>
#include <string>

namespace poros
{

class TimeKeeper
{
  public:
    enum {
      TOTAL,
      COARSENING,
      AGGREGATION,
      CONTRACTION,
      INITIAL_PARTITIONING,
      UNCOARSENING,
      REFINEMENT,
      PROJECTION,
      NUM_TIME_CATEGORIES
    };

    /**
    * @brief Default constructor.
    */
    TimeKeeper();

    /**
    * @brief Deleted copy constructor.
    *
    * @param rhs The TimeKeeper to copy.
    */
    TimeKeeper(
        TimeKeeper const & rhs) = delete;

    /**
    * @brief Deleted copy-assignment operator.
    *
    * @param rhs The TimeKeeper to copy.
    *
    * @return This TimeKeeper.
    */
    TimeKeeper& operator=(
        TimeKeeper const & rhs) = delete;

    /**
     * @brief Add time to a given key. 
     *
     * @param key The key.
     * @param seconds The time to add.
     *
     * @throws An exception if key has not been added before.
     */
    void reportTime(
        uint32_t key,
        double seconds);

    /**
     * @brief Get the times associated with this object.
     *
     * @return The times.
     */
    std::vector<std::pair<std::string, double>> times() const;

  private:
    std::vector<double> m_times;
    std::vector<std::string> m_names;
};

}

#endif
