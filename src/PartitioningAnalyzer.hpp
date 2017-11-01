/**
* @file PartitioningAnalyzer.hpp
* @brief The PartitioningAnalyzer class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-31
*/



#ifndef DOLOS_SRC_PARTITIONINGANALYZER_HPP
#define DOLOS_SRC_PARTITIONINGANALYZER_HPP


#include "Base.hpp"
#include "Partitioning.hpp"
#include "TargetPartitioning.hpp"
#include "Debug.hpp"


namespace dolos
{


class PartitioningAnalyzer
{
  public:
    /**
    * @brief Create a new partitioning analyzer.
    *
    * @param part The current partitioning.
    * @param target The target partitioning.
    */
    PartitioningAnalyzer(
        Partitioning const * part,
        TargetPartitioning const * target);


    /**
    * @brief Get the maximum imbalance as a fraction. That is, if a partition
    * is 5% overweight, this function will return 0.05.
    *
    * @return The maximum imbalance.
    */
    double calcMaxImbalance() const;


    /**
    * @brief Get whether the given partition is overweight.
    *
    * @param part The partition.
    *
    * @return Whether or not the partition is overweight.
    */
    bool isOverWeight(
        pid_type part) const noexcept
    {
      return m_target->getMaxWeight(part) < m_partitioning->getWeight(part);
    }

  private:
    Partitioning const * const m_partitioning;
    TargetPartitioning const * const m_target;

};

}


#endif
