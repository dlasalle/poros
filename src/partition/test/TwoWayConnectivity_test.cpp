/**
* @file TwoWayConnectivity_test.cpp
* @brief Unit tests for the TwoWayConnectivity class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-20
*/



#include "partition/TwoWayConnectivity.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"



namespace poros
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


  Graph g = gen.generate();

  Partitioning p(2, &g);

  p.assign(Vertex::make(0), 0);
  p.assign(Vertex::make(1), 0);
  p.assign(Vertex::make(2), 0);
  p.assign(Vertex::make(3), 1);

  p.recalcCutEdgeWeight();

  TwoWayConnectivity conn = TwoWayConnectivity::fromPartitioning(&g, &p);

  // moving any vertex should increase the cut by 1
  testEqual(conn.getVertexDelta(0), 2);
  testEqual(conn.getVertexDelta(1), 0);
  testEqual(conn.getVertexDelta(2), 0);
  testEqual(conn.getVertexDelta(3), -2);
}


UNITTEST(TwoWayConnectivity, Move)
{
  GridGraphGenerator gen(2,2,2);

  Graph g = gen.generate();

  Partitioning p(2, &g);

  p.assign(Vertex::make(0), 0);
  p.assign(Vertex::make(1), 0);
  p.assign(Vertex::make(2), 0);
  p.assign(Vertex::make(3), 0);

  p.assign(Vertex::make(4), 1);
  p.assign(Vertex::make(5), 1);
  p.assign(Vertex::make(6), 1);
  p.assign(Vertex::make(7), 1);

  p.recalcCutEdgeWeight();
  TwoWayConnectivity conn = TwoWayConnectivity::fromPartitioning(&g, &p);

  testEqual(conn.getVertexDelta(0), 1);

  conn.move(Vertex::make(0));

  testEqual(conn.getVertexDelta(0), -1);
}

UNITTEST(TwoWayConnectivity, UpdateNeighbor)
{
  GridGraphGenerator gen(2,2,2);

  Graph g = gen.generate();
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

  Partitioning p(2, &g);

  p.assign(Vertex::make(0), 0);
  p.assign(Vertex::make(1), 0);
  p.assign(Vertex::make(2), 0);
  p.assign(Vertex::make(3), 0);

  p.assign(Vertex::make(4), 1);
  p.assign(Vertex::make(5), 1);
  p.assign(Vertex::make(6), 1);
  p.assign(Vertex::make(7), 1);

  p.recalcCutEdgeWeight();
  TwoWayConnectivity conn = TwoWayConnectivity::fromPartitioning(&g, &p);

  p.move(Vertex::make(1), 1);
  conn.move(Vertex::make(1));
  for (Edge const & edge : g.edgesOf(Vertex::make(1))) {
    Vertex const u = g.destinationOf(edge);
    pid_type const where = p.getAssignment(u);
    int const status = \
        conn.updateNeighbor(u, g.weightOf(edge), \
        TwoWayConnectivity::getDirection(1, where));
    if (u == 5) {
      testEqual(status, TwoWayConnectivity::BORDER_REMOVED);
    } else {
      testEqual(status, TwoWayConnectivity::BORDER_STILLIN);
    }
  }

  testTrue(conn.isInBorder(Vertex::make(0)));
  testTrue(conn.isInBorder(Vertex::make(1)));
  testTrue(conn.isInBorder(Vertex::make(2)));
  testTrue(conn.isInBorder(Vertex::make(3)));
  testTrue(conn.isInBorder(Vertex::make(4)));
  testFalse(conn.isInBorder(Vertex::make(5)));
  testTrue(conn.isInBorder(Vertex::make(6)));
  testTrue(conn.isInBorder(Vertex::make(7)));

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

  Graph g = gen.generate();

  Partitioning p(2, &g);

  // back face
  p.assign(Vertex::make(0), 0);
  p.assign(Vertex::make(1), 0);
  p.assign(Vertex::make(4), 0);
  p.assign(Vertex::make(5), 0);

  // front face
  p.assign(Vertex::make(2), 1);
  p.assign(Vertex::make(3), 1);
  p.assign(Vertex::make(6), 1);
  p.assign(Vertex::make(7), 1);

  p.recalcCutEdgeWeight();

  TwoWayConnectivity conn = TwoWayConnectivity::fromPartitioning(&g, &p);

  // moving any vertex should increase the cut by 1
  testEqual(conn.getVertexDelta(0), 1);
  testEqual(conn.getVertexDelta(1), 1);
  testEqual(conn.getVertexDelta(2), 1);
  testEqual(conn.getVertexDelta(3), 1);
  testEqual(conn.getVertexDelta(4), 1);
  testEqual(conn.getVertexDelta(5), 1);
  testEqual(conn.getVertexDelta(6), 1);
  testEqual(conn.getVertexDelta(7), 1);

  conn.move(Vertex::make(0));
  p.move(Vertex::make(0), 1);
  for (Edge const & edge : g.edgesOf(Vertex::make(0))) {
    pid_type const where = p.getAssignment(g.destinationOf(edge));
    conn.updateNeighbor(g.destinationOf(edge), g.weightOf(edge), \
        TwoWayConnectivity::getDirection(1, where));
  }

  testEqual(conn.getVertexDelta(0), -1);
  testEqual(conn.getVertexDelta(1), -1);
  testEqual(conn.getVertexDelta(2), 3);
  testEqual(conn.getVertexDelta(4), -1);

  conn.move(Vertex::make(2));
  p.move(Vertex::make(2), 0);
  for (Edge const & edge : g.edgesOf(Vertex::make(2))) {
    pid_type const where = p.getAssignment(g.destinationOf(edge));
    conn.updateNeighbor(g.destinationOf(edge), g.weightOf(edge), \
        TwoWayConnectivity::getDirection(0, where));
  }

  testEqual(conn.getVertexDelta(0), -3);
  testEqual(conn.getVertexDelta(1), -1);
  testEqual(conn.getVertexDelta(2), -3);
  testEqual(conn.getVertexDelta(4), -1);

  conn.move(Vertex::make(0));
  p.move(Vertex::make(0), 0);
  for (Edge const & edge : g.edgesOf(Vertex::make(0))) {
    pid_type const where = p.getAssignment(g.destinationOf(edge));
    conn.updateNeighbor(g.destinationOf(edge), g.weightOf(edge), \
        TwoWayConnectivity::getDirection(0, where));
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


  Graph g = gen.generate();

  Partitioning p(2, &g);

  p.assign(Vertex::make(0), 0);
  p.assign(Vertex::make(1), 0);
  p.assign(Vertex::make(2), 1);
  p.assign(Vertex::make(3), 0);
  p.assign(Vertex::make(4), 1);
  p.assign(Vertex::make(5), 1);

  p.recalcCutEdgeWeight();

  TwoWayConnectivity conn = TwoWayConnectivity::fromPartitioning(&g, &p);

  sl::FixedSet<vtx_type> const * const bnd = conn.getBorderVertexSet();

  testEqual(bnd->size(), 4u);

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


UNITTEST(TwoWayConnectivity, Verify)
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

  Graph g = gen.generate();

  Partitioning p(2, &g);

  // back face
  p.assign(Vertex::make(0), 0);
  p.assign(Vertex::make(1), 0);
  p.assign(Vertex::make(4), 0);
  p.assign(Vertex::make(5), 0);

  // front face
  p.assign(Vertex::make(2), 1);
  p.assign(Vertex::make(3), 1);
  p.assign(Vertex::make(6), 1);
  p.assign(Vertex::make(7), 1);

  p.recalcCutEdgeWeight();

  TwoWayConnectivity conn = TwoWayConnectivity::fromPartitioning(&g, &p);

  testTrue(conn.verify(&g, &p));

  conn.move(Vertex::make(0));
  p.move(Vertex::make(0), 1);
  for (Edge const edge : g.edgesOf(Vertex::make(0))) {
    pid_type const where = p.getAssignment(g.destinationOf(edge));
    conn.updateNeighbor(g.destinationOf(edge), g.weightOf(edge), \
        TwoWayConnectivity::getDirection(1, where));
  }
  testTrue(conn.verify(&g, &p));

  conn.move(Vertex::make(2));
  p.move(Vertex::make(2), 0);
  for (Edge const edge : g.edgesOf(Vertex::make(2))) {
    pid_type const where = p.getAssignment(g.destinationOf(edge));
    conn.updateNeighbor(g.destinationOf(edge), g.weightOf(edge), \
        TwoWayConnectivity::getDirection(0, where));
  }
  testTrue(conn.verify(&g, &p));

  conn.move(Vertex::make(0));
  p.move(Vertex::make(0), 0);
  for (Edge const edge : g.edgesOf(Vertex::make(0))) {
    pid_type const where = p.getAssignment(g.destinationOf(edge));
    conn.updateNeighbor(g.destinationOf(edge), g.weightOf(edge), \
        TwoWayConnectivity::getDirection(0, where));
  }

  testTrue(conn.verify(&g, &p));
}


}
