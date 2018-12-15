/**
* @file ICoarseGraph.hpp
* @brief The ICoarseGraph interface.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-10
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


#ifndef POROS_SRC_MULTILEVEL_ICOARSEGRAPH_HPP
#define POROS_SRC_MULTILEVEL_ICOARSEGRAPH_HPP


#include "graph/GraphHandle.hpp"
#include "partition/Partitioning.hpp"
#include "partition/PartitioningInformation.hpp"

namespace poros
{


class ICoarseGraph
{
  public:
  /**
  * @brief Virtual destructor.
  */
  virtual ~ICoarseGraph()
  {
    // do nothing
  }


  /**
  * @brief Get the coarsened graph.
  *
  * @return The coarsened graph.
  */
  virtual Graph const * graph() const = 0;


  /**
  * @brief Project the partitioning of the coarse graph to the fine graph.
  *
  * @param coarseInfo The partitioning information of the coarse graph.
  *
  * @return The partitioning information of the fine graph.
  */
  virtual PartitioningInformation project(
      PartitioningInformation const * coarseInfo) = 0;



};


}

#endif
