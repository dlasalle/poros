/**
* @file TimedProcess.cpp
* @brief 
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
*/

#include "TimedProcess.hpp"


namespace poros
{

/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

TimedProcess::TimedProcess() :
  m_timeKeeper(nullptr)
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


void TimedProcess::setTimeKeeper(
    std::shared_ptr<TimeKeeper> const & timeKeeper)
{
  m_timeKeeper = timeKeeper;
}


/******************************************************************************
* PROTECTED METHODS ***********************************************************
******************************************************************************/


void TimedProcess::reportTime(
    int const category,
    double const time)
{
  if (m_timeKeeper.get() != nullptr) {
    m_timeKeeper->reportTime(category, time);
  }
}


}

