/**
* @file TimedContractor.cpp
* @brief Implementation of the TimedContractor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-10
*/


#include "TimedContractor.hpp"
#include  "solidutils/Timer.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

TimedContractor::TimedContractor(
    std::unique_ptr<IContractor> contractor) :
  m_contractor(std::move(contractor))
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

GraphHandle TimedContractor::contract(
    Graph const * const graph,
    Aggregation const * const aggregation)
{
  sl::Timer tmr;
  tmr.start();

  GraphHandle coarse = m_contractor->contract(graph, aggregation);

  tmr.stop();
  reportTime(TimeKeeper::CONTRACTION, tmr.poll());

  return coarse;
}


}
