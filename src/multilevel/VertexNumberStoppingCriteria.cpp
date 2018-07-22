/**
 * @file VertexNumberStoppingCriteria.cpp
 * @brief Implementation of the VertexNumberStoppingCriteria.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-07-22
 */

#include "VertexNumberStoppingCriteria.hpp"

namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

VertexNumberStoppingCriteria::VertexNumberStoppingCriteria(
    vtx_type const numVertices) :
  m_numVertices(numVertices)
{
  // do nothing
}

/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

bool VertexNumberStoppingCriteria::shouldStop(
    int const, // level unused
    ConstantGraph const * const, // fine graph unused
    ConstantGraph const * const coarse) const
{
  return coarse->numVertices() <= m_numVertices;
}


}
