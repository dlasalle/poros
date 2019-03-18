/**
 * @file Base.hpp
 * @brief Base type aliases and constants.
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


#ifndef POROS_SRC_BASE_HPP
#define POROS_SRC_BASE_HPP


#include "poros.h"

#include <limits>

namespace poros
{

/******************************************************************************
* ALIASES *********************************************************************
******************************************************************************/

typedef poros_vtx_type vtx_type;
typedef poros_adj_type adj_type;
typedef poros_wgt_type wgt_type;
typedef poros_pid_type pid_type;

typedef int32_t wgt_diff_type; 


/******************************************************************************
* CONSTANTS *******************************************************************
******************************************************************************/

namespace
{

constexpr vtx_type const NULL_VTX = std::numeric_limits<vtx_type>::max();
constexpr adj_type const NULL_ADJ = std::numeric_limits<adj_type>::max();
constexpr wgt_type const NULL_WGT = std::numeric_limits<wgt_type>::max();
constexpr pid_type const NULL_PID = std::numeric_limits<pid_type>::max();

pid_type const LEFT_PARTITION = 0;
pid_type const RIGHT_PARTITION = 1;
pid_type const NUM_BISECTION_PARTS = 2;

}


}


#endif
