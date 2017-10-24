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
#include "Partitioning.hpp"
#include "Debug.hpp"


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
        double const * fractions = nullptr);


    /**
    * @brief Get the maximum allowable partition weights.
    *
    * @return The maximum weights.
    */
    double const * getMaxWeight() const;


    /**
    * @brief Get the maximum imbalance as a fraction. That is, if a partition
    * is 5% overweight, this function will return 0.05.
    *
    * @param partitioning The partitioning to check.
    *
    * @return The maximum imbalance.
    */
    double calcMaxImbalance(
        Partitioning const * partitioning) const;


    /**
    * @brief Get the maximum weight allowed by a partition.
    *
    * @param part The partition.
    *
    * @return The maximum weight.
    */
    inline double getMaxWeight(
        pid_type const part) const noexcept
    {
      ASSERT_LESS(part, m_numParts);

      m_maxWeight[part];
    }


  private:
    pid_type m_numPartitions;
    wgt_type m_totalVertexWeight;
    double m_imbalanceTolerance;
    Array<double> m_fractions;
    Array<wgt_type> m_targetWeight; 
    Array<wgt_type> m_maxWeight; 
};


}

#endif
