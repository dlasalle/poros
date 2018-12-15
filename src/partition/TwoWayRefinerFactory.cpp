/**
* @file TwoWayRefinerFactory.cpp
* @brief Implementation of the TwoWayRefinerFactory class.
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


#include "TwoWayRefinerFactory.hpp"
#include "FMRefiner.hpp"
#include "TimedTwoWayRefiner.hpp"


namespace poros
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

