/**
* @file TimedTwoWayRefiner.hpp
* @brief The TimedTwoWayRefiner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-02
*/


#ifndef POROS_SRC_TIMEDTWOWAYREFINER_HPP
#define POROS_SRC_TIMEDTWOWAYREFINER_HPP

#include "ITwoWayRefiner.hpp"
#include "util/TimedProcess.hpp"

namespace poros
{

class TimedTwoWayRefiner : public ITwoWayRefiner, public TimedProcess
{
  public:
    /**
    * @brief Create a new time two way refiner.
    *
    * @param refiner The refiner to wrap.
    */
    TimedTwoWayRefiner(
        std::unique_ptr<ITwoWayRefiner> refiner);

    /**
    * @brief Refine the partition for the given graph.
    *
    * @param params The parameters of the bisection.
    * @param partitioning The partitioning (input and output).
    * @param connectivity The connectivity of vertices to the partitions.
    * @param graph The graph.
    */
    void refine(
        TargetPartitioning const * target,
        TwoWayConnectivity * connectivity,
        Partitioning * partitioning,
        Graph const * graph) override;

    private:
      std::unique_ptr<ITwoWayRefiner> m_refiner;
};

}

#endif

