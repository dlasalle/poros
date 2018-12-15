/**
* @file MultilevelPartitioner.cpp
* @brief Implementation of the MultilevelPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-04
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


#include "MultilevelPartitioner.hpp"

namespace poros
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

MultilevelPartitioner::MultilevelPartitioner(
    std::unique_ptr<IAggregator> aggregator,
    std::unique_ptr<IPartitioner> initialPartitioner,
    std::unique_ptr<IRefiner> refiner) :
  m_aggregator(std::move(aggregator)),
  m_initialPartitioner(std::move(initialPartitioner)),
  m_refiner(std::move(refiner))
{
  // do nothing 
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


Partitioning MultilevelPartitioner::execute(
    TargetPartitioning const * const target,
    Graph const * const graph)
{
  Partitioning part(target->numPartitions(), graph);

  // aggregate

  // contract

  // partition

  // project

  // refine

  return part;
}



}
