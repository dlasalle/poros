/**
* @file TwoWayConnectivityBuilder_test.cpp
* @brief Unit tests for the TwoWayConnectivityBuilder.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-12-12
*/

#include "partition/TwoWayConnectivityBuilder.hpp"
#include "solidutils/UnitTest.hpp"


namespace poros
{


/******************************************************************************
* UNIT TESTS ******************************************************************
******************************************************************************/

UNITTEST(TwoWayConnectivityBuilderTest, BuildTest)
{
  TwoWayConnectivityBuilder builder;

  builder.begin(4UL);

  builder.setInternalConnectivityOf(Vertex::make(0), static_cast<wgt_type>(1));
  builder.setExternalConnectivityOf(Vertex::make(0), static_cast<wgt_type>(1));
  builder.setInternalConnectivityOf(Vertex::make(1), static_cast<wgt_type>(1));
  builder.setExternalConnectivityOf(Vertex::make(1), static_cast<wgt_type>(0));
  builder.setInternalConnectivityOf(Vertex::make(2), static_cast<wgt_type>(0));
  builder.setExternalConnectivityOf(Vertex::make(2), static_cast<wgt_type>(1));
  builder.setInternalConnectivityOf(Vertex::make(3), static_cast<wgt_type>(0));
  builder.setExternalConnectivityOf(Vertex::make(3), static_cast<wgt_type>(0));

  TwoWayConnectivity conn = builder.finish();

  testEqual(conn.internalConnectivityOf(Vertex::make(0)), static_cast<wgt_type>(1));
  testEqual(conn.externalConnectivityOf(Vertex::make(0)), static_cast<wgt_type>(1));
  testEqual(conn.internalConnectivityOf(Vertex::make(1)), static_cast<wgt_type>(1));
  testEqual(conn.externalConnectivityOf(Vertex::make(1)), static_cast<wgt_type>(0));
  testEqual(conn.internalConnectivityOf(Vertex::make(2)), static_cast<wgt_type>(0));
  testEqual(conn.externalConnectivityOf(Vertex::make(2)), static_cast<wgt_type>(1));
  testEqual(conn.internalConnectivityOf(Vertex::make(3)), static_cast<wgt_type>(0));
  testEqual(conn.externalConnectivityOf(Vertex::make(3)), static_cast<wgt_type>(0));
}

}

