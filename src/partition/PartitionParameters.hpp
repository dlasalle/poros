/**
 * @file PartitionParameters.hpp
 * @brief The PartitionParameters class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018
 * @version 1
 * @date 2017-10-04
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


#ifndef POROS_SRC_PARTITIONPARAMETERS_HPP
#define POROS_SRC_PARTITIONPARAMETERS_HPP


#include <vector>
#include <string>
#include <stdexcept>
#include "Base.hpp"


namespace poros
{


class InvalidPartitionParametersException :
  public std::runtime_error
{
  public:
    InvalidPartitionParametersException(
        std::string msg) :
      runtime_error(msg)
    {
      // do nothing
    }
};


class PartitionParameters
{
  public:
    /**
     * @brief Construct a new set of parameters given the options.
     *
     * @param numPartitions The number of partitions to create.
     */
    PartitionParameters(
        pid_type numPartitions);


    /**
    * @brief The fraction of imbalance tolerance to accept (e.g., 0.03 is %3).
    *
    * @param toleranceFraction The fraction.
    */
    void setImbalanceTolerance(
        double toleranceFraction);


    /**
    * @brief Set the weight fraction targerts for each partition.
    *
    * @param fractions The target weight fractions.
    */
    void setTargetPartitionFractions(
        double const * fractions);


    /**
     * @brief Get the maximum allowed imbalance (as a fraction). That is, 3%
     * imbalance would be a value of 0.03.
     *
     * @return The imbalance tolerance.
     */
    double getImbalanceTolerance() const;


    /**
     * @brief Get the number of partitions.
     *
     * @return The number of partitions.
     */
    pid_type numPartitions() const;


    /**
     * @brief Get the target partition fractions.
     *
     * @return The target partition fractions.
     */
    double const * getTargetPartitionFractions() const;


   private:
    pid_type m_numParts;
    double m_imbalanceTolerance;
    std::vector<double> m_targetPartitionFractions;
};

}

#endif
