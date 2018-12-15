/**
* @file SHEMRMAggregator.hpp
* @brief The SHEMRMAggregator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-10
*/


#ifndef POROS_SRC_SHEMRMAGGREGATOR_HPP
#define POROS_SRC_SHEMRMAGGREGATOR_HPP


#include "IAggregator.hpp"
#include "RandomMatchingAggregator.hpp"
#include "HeavyEdgeMatchingAggregator.hpp"

namespace poros
{

class SHEMRMAggregator : public IAggregator
{
  public:
    /**
    * @brief Create a new SHEM/RM aggregator.
    *
    * @param rng The random engine handle.
    */
    SHEMRMAggregator(
        RandomEngineHandle rng);

    
    /**
    * @brief Deleted copy constructor.
    *
    * @param rhs The aggregator to copy.
    */
    SHEMRMAggregator(
        SHEMRMAggregator const & rhs) = delete;


    /**
    * @brief Deleted assignment operator.
    *
    * @param rhs The aggregator to copy from.
    *
    * @return This aggregator.
    */
    SHEMRMAggregator& operator=(
        SHEMRMAggregator const & rhs) = delete;


    /**
    * @brief Virtual destructor.
    */
    virtual ~SHEMRMAggregator() = default;


    /**
    * @brief Generate an aggregation of the graph.
    *
    * @param graph The graph to aggregate.
    *
    * @return The aggregation.
    */
    Aggregation aggregate(
        AggregationParameters params,
        Graph const * graph);

  private:
      HeavyEdgeMatchingAggregator m_shem;
      RandomMatchingAggregator m_rm;
};

}

#endif
