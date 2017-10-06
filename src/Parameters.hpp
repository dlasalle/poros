/**
 * @file Parameters.hpp
 * @brief The Parameters class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#ifndef DOLOS_SRC_PARAMETERS_HPP
#define DOLOS_SRC_PARAMETERS_HPP


#include <vector>
#include <string>
#include <stdexcept>
#include "Base.hpp"


namespace dolos
{


class InvalidParametersException :
  public std::runtime_error
{
  public:
    InvalidParametersException(
        std::string msg) :
      runtime_error(msg)
    {
      // do nothing
    }
};


class Parameters
{
  public:
    /**
     * @brief Construct a new set of parameters given the options.
     *
     * @param numPartitions The number of partitions to create.
     * @param options The options.
     */
    Parameters(
        pid_type numPartitions,
        dolos_options_struct const * const options);

    /**
     * @brief Get the random seed in use.
     *
     * @return The random seed.
     */
    unsigned int getSeed() const;

    /**
     * @brief Get the maximum allowed imbalance (as a fraction). That is, 3%
     * imbalance would be a value of 0.03.
     *
     * @return The imbalance tolerance.
     */
    double getImbalanceTolerance() const;

    /**
     * @brief Get the number of refinement iterations to use.
     *
     * @return The number of refinement iterations.
     */
    int getNumRefinementIterations() const;

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
    std::vector<double> const * getTargetPartitionFractions() const;

    /**
     * @brief Get the maximum vertex weight allowed per partition.
     *
     * @return The maximum allowed vertex weight;
     */
    std::vector<wgt_type> const * getMaxPartitionWeights() const;

   private:
    unsigned int m_seed;
    int m_numRefinementIterations;
    pid_type m_numParts;
    double m_imbalanceTolerance;
    std::vector<double> m_targetPartitionFractions;
    std::vector<wgt_type> m_maxPartitionWeights;
};

}

#endif
