/**
* @file TargetPartitioning.hpp
* @brief The TargetPartitioning class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-24
*/




#ifndef DOLOS_SRC_TARGETPARTITIONING_HPP
#define DOLOS_SRC_TARGETPARTITIONING_HPP


#include "Base.hpp"
#include "solidutils/Array.hpp"
#include "solidutils/Debug.hpp"


namespace dolos
{


class InvalidPartitionFractionsException :
    public std::runtime_error
{
  public:
    InvalidPartitionFractionsException(
        std::string msg) :
      std::runtime_error(msg)
    {
      // do nothing 
    }
};


class TargetPartitioning
{
  public:
    /**
    * @brief Create a new target partitioning with uniform partitions.
    *
    * @param numPartitions The number of partitions (k).
    * @param totalVertexWeight The total vertex weight.
    * @param imbalanceTolerance The allowable imbalance tolerance.
    */
    TargetPartitioning(
        pid_type numPartitions,
        wgt_type totalVertexWeight,
        double imbalanceTolerance);


    /**
    * @brief Create a new target partitioning with the specified partition
    * fractions.
    *
    * @param numPartitions The number of partitions (k).
    * @param totalVertexWeight The total vertex weight.
    * @param imbalanceTolerance The allowable imbalance tolerance.
    * @param fractions The target partition fractions.
    */
    TargetPartitioning(
        pid_type numPartitions,
        wgt_type totalVertexWeight,
        double imbalanceTolerance,
        double const * fractions);


    /**
    * @brief Get the maximum allowable partition weights.
    *
    * @return The maximum weights.
    */
    wgt_type const * getMaxWeight() const;


    /**
    * @brief Get the maximum weight allowed by a partition.
    *
    * @param part The partition.
    *
    * @return The maximum weight.
    */
    inline wgt_type getMaxWeight(
        pid_type const part) const noexcept
    {
      ASSERT_LESS(part, m_numPartitions);

      return m_maxWeight[part];
    }


    /**
    * @brief Get the target weight for a given partition.
    *
    * @param part The partition.
    *
    * @return The target weight.
    */
    inline wgt_type getTargetWeight(
         pid_type const part) const noexcept
    {
      ASSERT_LESS(part, m_numPartitions);

      return m_targetWeight[part];
    }


  private:
    pid_type m_numPartitions;
    wgt_type m_totalVertexWeight;
    double m_imbalanceTolerance;
    sl::Array<double> m_fractions;
    sl::Array<wgt_type> m_targetWeight; 
    sl::Array<wgt_type> m_maxWeight; 
};


}

#endif
