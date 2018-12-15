/**
* @file BisectorFactory.cpp
* @brief The implementation of the BisectorFactory class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
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

#include "BisectorFactory.hpp"
#include "RandomBisector.hpp"
#include "BFSBisector.hpp"
#include "MultiBisector.hpp"
#include "TimedBisector.hpp"

namespace poros
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
