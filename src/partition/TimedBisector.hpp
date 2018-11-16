/**
* @file TimedBisector.hpp
* @brief The TimedBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
*/



#ifndef DOLOS_SRC_TIMEDBISECTOR_HPP
#define DOLOS_SRC_TIMEDBISECTOR_HPP

#include "IBisector.hpp"
#include "util/TimedProcess.hpp"

namespace dolos
{

class TimedBisector : public IBisector, public TimedProcess
{
  public:
    /**
    * @brief Create a new timed bisector, wrapping an existing bisector.
    *
    * @param bisector The bisector to wrap.
    */
    TimedBisector(
        std::unique_ptr<IBisector> bisector);

    /**
    * @brief Create an aggregation of the graph.
    *
    * @param target The target partitioning.
    * @param graph The graph to aggregate.
    *
    * @return The aggregation.
    */
    Partitioning execute(
        TargetPartitioning const * target,
        Graph const * graph) override;

  private:
    std::unique_ptr<IBisector> m_bisector;


};


}



#endif
