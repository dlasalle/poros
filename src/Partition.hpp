/**
* @file Partition.hpp
* @brief The Partition class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-11-03
*/


#ifndef DOLOS_SRC_PARTITION_HPP
#define DOLOS_SRC_PARTITION_HPP


#include "Base.hpp"


namespace dolos
{


class Partition
{
  public:
    /**
    * @brief Create a new partition.
    *
    * @param index The index of the partition.
    * @param partitionWeight The vector of partition weights.
    */
    Partition(
        pid_type const index,
        wgt_type const * const partitionWeight) noexcept :
      m_index(index),
      m_partitionWeight(partitionWeight)
    {
      // do nothing
    }


    /**
    * @brief Get the index of this partition (it's ID).
    *
    * @return The index.
    */
    inline pid_type index() const noexcept
    {
      return m_index;
    }


    /**
    * @brief Get weight of the partition.
    *
    * @return The weight.
    */
    inline wgt_type weight() const noexcept
    {
      return m_partitionWeight[m_index];
    }

    private:
      adj_type m_index;
      wgt_type const * const m_partitionWeight;
};


}


#endif
