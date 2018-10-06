/**
 * @file TimeKeeper.h
 * @brief The TimeKeeper class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-09-25
 */


#ifndef DOLOS_SRC_UTIL_TIMEKEEPER_HPP
#define DOLOS_SRC_UTIL_TIMEKEEPER_HPP

#include <cstdint>
#include <vector>
#include <utility>
#include <string>

namespace dolos
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
