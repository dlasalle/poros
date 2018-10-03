/**
* @file TimedProcess.hpp
* @brief The TimedProcess class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
*/



#ifndef DOLOS_SRC_TIMEDPROCESS_HPP
#define DOLOS_SRC_TIMEDPROCESS_HPP

#include "TimeKeeper.hpp"

#include <memory>

namespace dolos
{

class TimedProcess
{
  public:
  /**
  * @brief Create a new timed process.
  */
  TimedProcess();
  
  /**
  * @brief Virtual destructor.
  */
  virtual ~TimedProcess() = default;

  /**
  * @brief Set the timekeeper for this process.
  *
  * @param timeKeeper The time keeper.
  */
  void setTimeKeeper(
      const std::shared_ptr<TimeKeeper>& timeKeeper);

  protected:
  /**
  * @brief Report times for this process.
  *
  * @param category The category of time.
  * @param time The time in seconds.
  */
  void reportTime(
      int category,
      double time);

  private:
  std::shared_ptr<TimeKeeper> m_timeKeeper;
};

}

#endif
