/**
 * @file DolosParameters.hpp
 * @brief The DolosParameters class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-08-26
 */



#ifndef DOLOS_SRC_DOLOSPARAMETERS_HPP
#define DOLOS_SRC_DOLOSPARAMETERS_HPP

#include "dolos.h"
#include "util/RandomEngineHandle.hpp"

namespace dolos
{


class DolosParameters
{
  public:
    /**
     * @brief Create a new set of parameters from an options struct.
     *
     * @param options The options struct (may be null).
     */
    DolosParameters(
        dolos_options_struct const * options);

    /**
     * @brief Get the current random engine to use.
     *
     * @return The random engine.
     */
    RandomEngineHandle randomEngine();

  private:
    RandomEngineHandle m_randomEngine;
};

}

#endif
