/**
* @file TwoWayRefinerFactory.cpp
* @brief Implementation of the TwoWayRefinerFactory class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
*/


#include "TwoWayRefinerFactory.hpp"
#include "FMRefiner.hpp"
#include "TimedTwoWayRefiner.hpp"


namespace dolos
{


/******************************************************************************
* PUBLIC STATIC METHODS *******************************************************
******************************************************************************/

std::unique_ptr<ITwoWayRefiner> TwoWayRefinerFactory::make(
    int const scheme)
{
  std::unique_ptr<ITwoWayRefiner> ptr;
  if (scheme == FM_TWOWAY_REFINEMENT) {
    ptr.reset(new FMRefiner(8, 150));
  } else {
    throw std::runtime_error("Unknown two way refinement type: " +
        std::to_string(scheme));
  }

  return ptr;
}


std::unique_ptr<ITwoWayRefiner> TwoWayRefinerFactory::make(
    int const scheme,
    std::shared_ptr<TimeKeeper> timeKeeper)
{
  std::unique_ptr<TimedTwoWayRefiner> ptr( \
      new TimedTwoWayRefiner(make(scheme)));

  ptr->setTimeKeeper(timeKeeper);

  return ptr;
}




}

