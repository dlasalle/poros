/**
* @file TargetPartitioning.hpp
* @brief The TargetPartitioning class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-24
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/




#ifndef POROS_SRC_TARGETPARTITIONING_HPP
#define POROS_SRC_TARGETPARTITIONING_HPP


#include <stdexcept>
#include "Base.hpp"
#include "solidutils/Array.hpp"
#include "solidutils/Debug.hpp"


namespace poros
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
    * @brief Create a new target partitioning with the specified partition
    * configuration.
    *
    * @param numPartitions The number of partitions (k).
    * @param fractions The fractions of weight for each partition.
    * @param targetWeights The target weight of each partition.
    * @param maxWeights The maximum allowable weight of each partition.
    */
    TargetPartitioning(
        pid_type numPartitions,
        sl::Array<wgt_type> targetWeights,
        sl::Array<wgt_type> maxWeights);


    /**
    * @brief Get the maximum allowable partition weights.
    *
    * @return The maximum weights.
    */
    wgt_type const * getMaxWeight() const;


    /**
    * @brief Get the target weight for all partitions.
    *
    * @return The target weights.
    */
    wgt_type const * getTargetWeight() const;


    /**
    * @brief Get the target fraction for all partitions.
    *
    * @return The target fractions.
    */
    double const * getTargetFraction() const;


    /**
    * @brief Get the target fraction for a given partition.
    *
    * @param part The partition.
    *
    * @return The target fraction.
    */
    inline double getTargetFraction(
         pid_type const part) const noexcept
    {
      ASSERT_LESS(part, m_numPartitions);

      return m_targetFraction[part];
    }


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


    /**
    * @brief Get the amount of weight which is allowed to be in excess for this
    * partition.
    *
    * @param part The partition.
    *
    * @return The amount of excess weight.
    */
    inline wgt_type getMaxExcessWeight(
         pid_type const part) const noexcept
    {
      ASSERT_LESS(part, m_numPartitions);
      ASSERT_GREATEREQUAL(m_maxWeight[part], m_targetWeight[part]);

      return m_maxWeight[part] - m_targetWeight[part];
    }


    /**
    * @brief Get the number of partitions to create.
    *
    * @return The number of partitions.
    */
    inline pid_type numPartitions() const noexcept
    {
      return m_numPartitions;
    }


  private:
    pid_type m_numPartitions;
    sl::Array<double> m_targetFraction;
    sl::Array<wgt_type> m_targetWeight; 
    sl::Array<wgt_type> m_maxWeight; 
};


}

#endif
