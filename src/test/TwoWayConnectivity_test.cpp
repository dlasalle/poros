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



namespace
{

UNITTEST(TwoWayConnectivity, Move)
{
  GridGraphGenerator gen(2,2,2);
  ConstantGraph g = gen.generate();

  Partitioning part(2, &g);
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

  testEqual(p.get

}


}
