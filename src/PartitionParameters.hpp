/**
 * @file PartitionParameters.hpp
 * @brief The PartitionParameters class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#ifndef DOLOS_SRC_PARTITIONPARAMETERS_HPP
#define DOLOS_SRC_PARTITIONPARAMETERS_HPP


#include <vector>
#include <string>
#include <stdexcept>
#include "Base.hpp"


namespace dolos
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
    pid_type getNumPartitions() const;

    /**
     * @brief Get the target partition fractions.
     *
     * @return The target partition fractions.
     */
    double const * getTargetPartitionFractions() const;

    /**
     * @brief Get the maximum partition fractions.
     *
     * @return The maximum partition fractions.
     */
    double const * getMaxPartitionFractions() const;



   private:
    pid_type m_numParts;
    double m_imbalanceTolerance;
    std::vector<double> m_targetPartitionFractions;
    std::vector<double> m_maxPartitionFractions;
};

}

#endif
