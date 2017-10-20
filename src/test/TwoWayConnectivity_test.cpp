/**
* @file TwoWayConnectivity_test.cpp
* @brief Unit tests for the TwoWayConnectivity class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-20
*/



#include "DomTest.hpp"
#include "TwoWayConnectivity.hpp"
#include "GridGraphGenerator.hpp"



namespace dolos
{

UNITTEST(TwoWayConnectivity, Move)
{
  GridGraphGenerator gen(2,2,2);
  ConstantGraph g = gen.generate();

  Partitioning p(2, &g);
  p.assign(0, 0);
  p.assign(1, 0);
  p.assign(4, 0);
  p.assign(5, 0);

  p.assign(2, 1);
  p.assign(3, 1);
  p.assign(6, 1);
  p.assign(7, 1);

  p.recalcCutEdgeWeight();

  TwoWayConnectivity conn(&g, &p);

  testEqual(conn.getVertexDelta(0), 1);
  testEqual(conn.getVertexDelta(1), 1);
  testEqual(conn.getVertexDelta(2), 1);
  testEqual(conn.getVertexDelta(3), 1);

  testEqual(conn.getVertexDelta(4), 1);
  testEqual(conn.getVertexDelta(5), 1);
  testEqual(conn.getVertexDelta(6), 1);
  testEqual(conn.getVertexDelta(7), 1);

  testEqual(p.getCutEdgeWeight(), 4);

  conn.move(0);
  conn.move(7);

  testEqual(p.getCutEdgeWeight(), 6);

  conn.move(0);
  conn.move(1);
  conn.move(7);

  testEqual(p.getCutEdgeWeight(), 5);
}


}
