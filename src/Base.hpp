/**
 * @file Base.hpp
 * @brief Base type aliases and constants.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#ifndef DOLOS_SRC_BASE_HPP
#define DOLOS_SRC_BASE_HPP


#include "dolos.h"

namespace dolos
{

/******************************************************************************
* ALIASES *********************************************************************
******************************************************************************/

typedef dolos_vtx_type vtx_type;
typedef dolos_adj_type adj_type;
typedef dolos_wgt_type wgt_type;
typedef dolos_pid_type pid_type;

typedef int32_t wgt_diff_type; 


/******************************************************************************
* CONSTANTS *******************************************************************
******************************************************************************/

namespace
{

vtx_type const NULL_VTX = static_cast<vtx_type>(-1);
adj_type const NULL_ADJ = static_cast<adj_type>(-1);
wgt_type const NULL_WGT = static_cast<wgt_type>(-1);
pid_type const NULL_PID = static_cast<pid_type>(-1);

pid_type const LEFT_PARTITION = 0;
pid_type const RIGHT_PARTITION = 1;
pid_type const NUM_BISECTION_PARTS = 2;

}


}


#endif
