/**
* @file TwoWayConnectivityBuilder_test.cpp
* @brief Unit tests for the TwoWayConnectivityBuilder.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-12-12
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

