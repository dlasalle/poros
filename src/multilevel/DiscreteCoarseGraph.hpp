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
#include "graph/ConstantGraph.hpp"
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
      ConstantGraph const * graph,
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
  ConstantGraph const * graph() const override;


  /**
  * @brief Project the partitioning of the coarse graph to the fine graph.
  *
  * @param coarsePartitioning The coarse graph.
  *
  * @return The partitioning of the fine graph.
  */
  Partitioning project(
      Partitioning const * coarsePartitioning) override;


  private:
  ConstantGraph const * m_fine;
  ConstantGraph m_coarse;
  sl::Array<vtx_type> m_coarseMap;
};

}


#endif
