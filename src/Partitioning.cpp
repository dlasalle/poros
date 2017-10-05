/**
* @file Partitioning.cpp
* @brief Implementation of the partitioning class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-04
*/


#include "Partitioning.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

Partitioning::Partitioning(
    pid_type const numParts,
    vtx_type const numVertices) :
  m_partitions(numParts, {0}),
  m_assignment(numVertices, NULL_PID)
{
  ASSERT_GREATER(numParts, 0);
  ASSERT_GREATER(numVertices, 0);
}


}
