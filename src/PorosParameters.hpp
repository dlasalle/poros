/**
 * @file PorosParameters.hpp
 * @brief The PorosParameters class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-08-26
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



#ifndef POROS_SRC_POROSPARAMETERS_HPP
#define POROS_SRC_POROSPARAMETERS_HPP

#include "poros.h"
#include "util/RandomEngineHandle.hpp"

namespace poros
{


class PorosParameters
{
  public:
    /**
     * @brief Create a new set of parameters from an options struct.
     *
     * @param options The options struct.
     */
    PorosParameters(
        poros_options_struct options);

    /**
     * @brief Get the current random engine to use.
     *
     * @return The random engine.
     */
    RandomEngineHandle randomEngine();

    /**
     * @brief Get the aggregation scheme to use.
     *
     * @return The aggregation scheme.
     */
    int aggregationScheme() const;

  private:
    RandomEngineHandle m_randomEngine;
    int m_aggregationScheme;
};

}

#endif
