/**
* @file PartitioningAnalyzer.hpp
* @brief The PartitioningAnalyzer class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-31
*/



#ifndef POROS_SRC_PARTITIONINGANALYZER_HPP
#define POROS_SRC_PARTITIONINGANALYZER_HPP


#include "Base.hpp"
#include "Partitioning.hpp"
#include "TargetPartitioning.hpp"
#include "solidutils/Debug.hpp"


namespace poros
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
    * @brief Get the current imbalance of a partition.
    *
    * @param part The partition.
    *
    * @return The imbalance.
    */
    inline double getImbalance(
        pid_type const part) const noexcept
    {
      double const target = m_target->getTargetFraction(part);
      ASSERT_GREATER(target, 0.0);
      return (static_cast<double>(m_partitioning->getFraction(part)) / \
          static_cast<double>(target)) - 1.0;
    }


    /**
    * @brief Get whether the given partition is overweight.
    *
    * @param part The partition.
    *
    * @return Whether or not the partition is overweight.
    */
    inline bool isOverWeight(
        pid_type const part) const noexcept
    {
      return m_target->getMaxWeight(part) < m_partitioning->getWeight(part);
    }


    /**
    * @brief CHeck if the partitioning is balanced.
    *
    * @return True if it is balanced.
    */
    inline bool isBalanced() const noexcept
    {
      bool balanced = true;
      for (Partition const & part : *m_partitioning) {
        balanced = balanced && !isOverWeight(part.index());
      }

      return balanced;
    }

  private:
    Partitioning const * const m_partitioning;
    TargetPartitioning const * const m_target;

};

}


#endif
