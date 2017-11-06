/**
* @file TwoWayConnectivity_test.cpp
* @brief Unit tests for the TwoWayConnectivity class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-20
*/



#include "solidutils/UnitTest.hpp"
#include "TwoWayConnectivity.hpp"
#include "GridGraphGenerator.hpp"



namespace dolos
{

UNITTEST(TwoWayConnectivity, GetDirection)
{
  testEqual(TwoWayConnectivity::getDirection(1, 1), \
      TwoWayConnectivity::MOVE_TOWARDS); 

  testEqual(TwoWayConnectivity::getDirection(0, 0), \
      TwoWayConnectivity::MOVE_TOWARDS); 

  testEqual(TwoWayConnectivity::getDirection(0, 1), \
      TwoWayConnectivity::MOVE_AWAY); 

  testEqual(TwoWayConnectivity::getDirection(1, 0), \
      TwoWayConnectivity::MOVE_AWAY); 
}


UNITTEST(TwoWayConnectivity, GetVertexDelta)
{
  GridGraphGenerator gen(2,2,1);
  /*
   * 0-------1
   *  \       \
   *   \       \
   *    2-------3
   */


  ConstantGraph g = gen.generate();

  Partitioning p(2, &g);

  p.assign(0, 0);
  p.assign(1, 0);
  p.assign(2, 0);
  p.assign(3, 1);

  p.recalcCutEdgeWeight();

  TwoWayConnectivity conn(&g, &p);

  // moving any vertex should increase the cut by 1
  testEqual(conn.getVertexDelta(0), 2);
  testEqual(conn.getVertexDelta(1), 0);
  testEqual(conn.getVertexDelta(2), 0);
  testEqual(conn.getVertexDelta(3), -2);
}


UNITTEST(TwoWayConnectivity, Move)
{
  GridGraphGenerator gen(2,2,2);

  ConstantGraph g = gen.generate();

  Partitioning p(2, &g);

  p.assign(0, 0);
  p.assign(1, 0);
  p.assign(2, 0);
  p.assign(3, 0);

  p.assign(4, 1);
  p.assign(5, 1);
  p.assign(6, 1);
  p.assign(7, 1);

  p.recalcCutEdgeWeight();
  TwoWayConnectivity conn(&g, &p);

  testEqual(conn.getVertexDelta(0), 1);

  conn.move(0);

  testEqual(conn.getVertexDelta(0), -1);
}

UNITTEST(TwoWayConnectivity, UpdateNieghbor)
{
  GridGraphGenerator gen(2,2,2);

  ConstantGraph g = gen.generate();

  Partitioning p(2, &g);

  p.assign(0, 0);
  p.assign(1, 0);
  p.assign(2, 0);
  p.assign(3, 0);

  p.assign(4, 1);
  p.assign(5, 1);
  p.assign(6, 1);
  p.assign(7, 1);

  p.recalcCutEdgeWeight();
  TwoWayConnectivity conn(&g, &p);

  for (Edge const & edge : g.getEdges(1)) {
    pid_type const where = p.getAssignment(edge.getVertex());
    conn.updateNeighbor(&edge, TwoWayConnectivity::getDirection(1, where));
  }

  testEqual(conn.getVertexDelta(0), -1);
  testEqual(conn.getVertexDelta(3), -1);
  testEqual(conn.getVertexDelta(5), 3);
}


UNITTEST(TwoWayConnectivity, MoveAndUpdate)
{
  GridGraphGenerator gen(2,2,2);
  /*
   * 0-------1
   * |\      |\
   * | \     | \
   * |  2-------3
   * 4--|----5  |
   *  \ |     \ |
   *   \|      \|
   *    6-------7
   */


  ConstantGraph g = gen.generate();

  Partitioning p(2, &g);

  // back face
  p.assign(0, 0);
  p.assign(1, 0);
  p.assign(4, 0);
  p.assign(5, 0);

  // front face
  p.assign(2, 1);
  p.assign(3, 1);
  p.assign(6, 1);
  p.assign(7, 1);

  p.recalcCutEdgeWeight();

  TwoWayConnectivity conn(&g, &p);

  // moving any vertex should increase the cut by 1
  testEqual(conn.getVertexDelta(0), 1);
  testEqual(conn.getVertexDelta(1), 1);
  testEqual(conn.getVertexDelta(2), 1);
  testEqual(conn.getVertexDelta(3), 1);
  testEqual(conn.getVertexDelta(4), 1);
  testEqual(conn.getVertexDelta(5), 1);
  testEqual(conn.getVertexDelta(6), 1);
  testEqual(conn.getVertexDelta(7), 1);

  conn.move(0);
  p.move(0, 1);
  for (Edge const & edge : g.getEdges(0)) {
    pid_type const where = p.getAssignment(edge.getVertex());
    conn.updateNeighbor(&edge, TwoWayConnectivity::getDirection(1, where));
  }

  testEqual(conn.getVertexDelta(0), -1);
  testEqual(conn.getVertexDelta(1), -1);
  testEqual(conn.getVertexDelta(2), 3);
  testEqual(conn.getVertexDelta(4), -1);

  conn.move(2);
  p.move(2, 0);
  for (Edge const & edge : g.getEdges(2)) {
    pid_type const where = p.getAssignment(edge.getVertex());
    conn.updateNeighbor(&edge, TwoWayConnectivity::getDirection(0, where));
  }

  testEqual(conn.getVertexDelta(0), -3);
  testEqual(conn.getVertexDelta(1), -1);
  testEqual(conn.getVertexDelta(2), -3);
  testEqual(conn.getVertexDelta(4), -1);

  conn.move(0);
  p.move(0, 1);
  for (Edge const & edge : g.getEdges(0)) {
    pid_type const where = p.getAssignment(edge.getVertex());
    conn.updateNeighbor(&edge, TwoWayConnectivity::getDirection(0, where));
  }

  testEqual(conn.getVertexDelta(0), 3);
  testEqual(conn.getVertexDelta(1), 1);
  testEqual(conn.getVertexDelta(2), -1);
  testEqual(conn.getVertexDelta(3), -1);
  testEqual(conn.getVertexDelta(4), 1);
  testEqual(conn.getVertexDelta(5), 1);
  testEqual(conn.getVertexDelta(6), -1);
  testEqual(conn.getVertexDelta(7), 1);
}

UNITTEST(TwoWayConnectivity, GetBorderSet)
{
  GridGraphGenerator gen(3,2,1);
  /*
   * 0---1---2
   *  \   \   \
   *   3---4---5
   */


  ConstantGraph g = gen.generate();

  Partitioning p(2, &g);

  p.assign(0, 0);
  p.assign(1, 0);
  p.assign(2, 1);
  p.assign(3, 0);
  p.assign(4, 1);
  p.assign(5, 1);

  p.recalcCutEdgeWeight();

  TwoWayConnectivity conn(&g, &p);

  sl::FixedSet<vtx_type> const * const bnd = conn.getBorderVertexSet();

  testEqual(bnd->size(), 4);

  std::vector<bool> map(6, false);

  for (vtx_type const & v : *bnd) {
    testFalse(map[v]);
    map[v] = true;
  }

  testTrue(map[1]);
  testTrue(map[2]);
  testTrue(map[3]);
  testTrue(map[4]);
}


}
