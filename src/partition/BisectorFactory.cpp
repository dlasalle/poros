/**
* @file BisectorFactory.cpp
* @brief The implementation of the BisectorFactory class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
*/

#include "BisectorFactory.hpp"
#include "RandomBisector.hpp"
#include "BFSBisector.hpp"
#include "MultiBisector.hpp"
#include "TimedBisector.hpp"

namespace dolos
{


/******************************************************************************
* PUBLIC STATIC METHODS *******************************************************
******************************************************************************/

std::unique_ptr<IBisector> BisectorFactory::make(
    int const scheme,
    RandomEngineHandle rng,
    int const numBisections)
{
  std::unique_ptr<IBisector> ptr;
  if (scheme == RANDOM_BISECTION) {
    ptr.reset(new RandomBisector(rng));
  } else if (scheme == BFS_BISECTION) {
    ptr.reset(new BFSBisector(rng));
  } else {
    throw std::runtime_error("Unknown bisector scheme: " +
        std::to_string(scheme));
  }

  return std::unique_ptr<IBisector>(new MultiBisector(numBisections, std::move(ptr)));
}


std::unique_ptr<IBisector> BisectorFactory::make(
    int const scheme,
    RandomEngineHandle rng,
    int const numBisections,
    std::shared_ptr<TimeKeeper> timeKeeper)
{
  std::unique_ptr<TimedBisector> ptr(new TimedBisector( \
      make(scheme, rng, numBisections)));
  ptr->setTimeKeeper(timeKeeper);

  return ptr;
}



}
