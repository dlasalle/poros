/**
* @file TimedTwoWayRefiner.cpp
* @brief Implementation of the TimedTwoWayRefiner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
*/


#include "TimedTwoWayRefiner.hpp"

#include "solidutils/Timer.hpp"

namespace poros
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

TimedTwoWayRefiner::TimedTwoWayRefiner(
    std::unique_ptr<ITwoWayRefiner> refiner) :
  m_refiner(std::move(refiner))
{
  // do nothing
}

/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void TimedTwoWayRefiner::refine(
    TargetPartitioning const * target,
    TwoWayConnectivity * connectivity,
    Partitioning * partitioning,
    Graph const * graph)
{
  sl::Timer tmr;
  tmr.start();

  m_refiner->refine(target, connectivity, partitioning, graph);

  tmr.stop();

  reportTime(TimeKeeper::REFINEMENT, tmr.poll());
}


}

