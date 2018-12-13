/**
* @file DiscreteCoarseGraph.hpp
* @brief The DiscreteCoarseGraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-10
*/



#ifndef DOLOS_SRC_MULTILEVEL_DISCRETECOARSEGRAPH_HPP
#define DOLOS_SRC_MULTILEVEL_DISCRETECOARSEGRAPH_HPP


#include "multilevel/ICoarseGraph.hpp"
#include "graph/Graph.hpp"
#include "aggregation/Aggregation.hpp"
#include "partition/Partitioning.hpp"

#include "solidutils/Array.hpp"

namespace dolos
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
