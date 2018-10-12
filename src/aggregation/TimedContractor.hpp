/**
* @file TimedContractor.hpp
* @brief The TimedAggregator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-10
*/


#ifndef DOLOS_SRC_TIMEDCONTRACTOR_HPP
#define DOLOS_SRC_TIMEDCONTRACTOR_HPP

#include "IContractor.hpp"
#include "util/TimedProcess.hpp"


namespace dolos
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
    ConstantGraph contract(
        ConstantGraph const * graph,
        Aggregation const * aggregation) override;

  private:
    std::unique_ptr<IContractor> m_contractor;


};


}

#endif

