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
    Parameters();

    unsigned int getSeed() const;

    int getNumRefinementIterations() const;

    pid_type getNumPartitions() const;

    std::vector<double> getTargetPartitionFractions() const;

   private:
    unsigned int m_seed;
    int m_numRefinementIterations;
    pid_type m_numParts;
    std::vector<double> m_constraints;
};

}

#endif
