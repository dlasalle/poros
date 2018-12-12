/**
* @file TwoWayConnectivityBuilder.cpp
* @brief Implementation of the TwoWayConnectivityBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-12-11
*/


#include "TwoWayConnectivityBuilder.hpp"



namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


TwoWayConnectivityBuilder::TwoWayConnectivityBuilder() :
  m_connectivity(0)
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void TwoWayConnectivityBuilder::begin(
    vtx_type const numVertices)
{
  m_connectivity = sl::Array<vertex_struct>(numVertices);
}


TwoWayConnectivity TwoWayConnectivityBuilder::finish()
{
  return TwoWayConnectivity(std::move(m_connectivity));
}




}

