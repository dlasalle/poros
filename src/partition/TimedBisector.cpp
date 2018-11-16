/**
* @file TimedBisector.cpp
* @brief Implementation of the TimedBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
*/

#include "TimedBisector.hpp"

#include "solidutils/Timer.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

TimedBisector::TimedBisector(
    std::unique_ptr<IBisector> bisector) :
  m_bisector(std::move(bisector))
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Partitioning TimedBisector::execute(
    TargetPartitioning const * target,
    Graph const * graph)
{
  sl::Timer tmr;
  tmr.start();

  Partitioning bisection = m_bisector->execute(target, graph);

  tmr.stop();

  reportTime(TimeKeeper::INITIAL_PARTITIONING, tmr.poll());

  return bisection;
}


}


