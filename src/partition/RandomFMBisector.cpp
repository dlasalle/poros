/**
* @file RandomFMBisector.cpp
* @brief Implementation of the RandomFMBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-11-06
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


#include "RandomFMBisector.hpp"


namespace poros
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

RandomFMBisector::RandomFMBisector(
    int maxIters,
    RandomEngineHandle randEngine) :
  m_bisector(randEngine),
  m_refiner(maxIters, 1000)
{
  // do nothing
}


RandomFMBisector::~RandomFMBisector()
{
  // do nothing
}


/******************************************************************************
* PUBLIC FUNCTIONS ************************************************************
******************************************************************************/

Partitioning RandomFMBisector::execute(
    TargetPartitioning const * const target,
    Graph const * const graph)
{
  Partitioning part = m_bisector.execute(target, graph);

  TwoWayConnectivity conn = TwoWayConnectivity::fromPartitioning(graph, &part);

  m_refiner.refine(target, &conn, &part, graph);

  return part;
}


}
