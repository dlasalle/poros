/**
* @file DiscreteCoarseGraph.hpp
* @brief The DiscreteCoarseGraph class.
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



#ifndef POROS_SRC_MULTILEVEL_DISCRETECOARSEGRAPH_HPP
#define POROS_SRC_MULTILEVEL_DISCRETECOARSEGRAPH_HPP


#include "multilevel/ICoarseGraph.hpp"
#include "graph/Graph.hpp"
#include "aggregation/Aggregation.hpp"
#include "partition/Partitioning.hpp"

#include "solidutils/Array.hpp"

namespace poros
{


class DiscreteCoarseGraph : public ICoarseGraph
{
  public:
  /**
  * @brief Create a new coarse graph.
  *
  * @param graph The graph.
  * @param agg The aggregation of the graph.
  */
  DiscreteCoarseGraph(
      Graph const * graph,
      Aggregation const * agg);

  /**
  * @brief Deleted copy constructor.
  *
  * @param rhs The discrete graph to copy.
  */
  DiscreteCoarseGraph(
      DiscreteCoarseGraph const & rhs) = delete;

  /**
  * @brief Deleted assignment operator.
  *
  * @param rhs The discrete graph to copy.
  *
  * @return This discrete graph.
  */
  DiscreteCoarseGraph& operator=(
      DiscreteCoarseGraph const & rhs) = delete;

  /**
  * @brief Get the coarsened graph.
  *
  * @return The coarsened graph.
  */
  Graph const * graph() const override;


  /**
  * @brief Project the partitioning of the coarse graph to the fine graph.
  *
  * @param coarseInfo The partitioning information of the coarse graph.
  *
  * @return The partitioning information of the fine graph.
  */
  PartitioningInformation project(
      PartitioningInformation const * coarseInfo) override;


  private:
  Graph const * m_fine;
  GraphHandle m_coarse;
  sl::Array<vtx_type> m_coarseMap;
};

}


#endif
