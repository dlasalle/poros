/**
* @file TimedContractor.hpp
* @brief The TimedAggregator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-10
*/


#ifndef POROS_SRC_TIMEDCONTRACTOR_HPP
#define POROS_SRC_TIMEDCONTRACTOR_HPP

#include "IContractor.hpp"
#include "util/TimedProcess.hpp"


namespace poros
{

class TimedContractor : public IContractor, public TimedProcess
{
  public:
    /**
    * @brief Create a new timed contractor, wrapping an existing contractor.
    *
    * @param contractor The contractor to wrap.
    */
    TimedContractor(
        std::unique_ptr<IContractor> contractor);

    /**
    * @brief Contract a graph.
    *
    * @param graph The graph to contract.
    * @param aggregation The aggregation specifying which vertices to aggregate
    * together.
    *
    * @return The aggregation.
    */
    GraphHandle contract(
        Graph const * graph,
        Aggregation const * aggregation) override;

  private:
    std::unique_ptr<IContractor> m_contractor;


};


}

#endif

