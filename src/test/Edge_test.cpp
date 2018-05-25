/**
* @file Edge_test.cpp
* @brief Unit tests for the Edge class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2018-01-13
*/



#include "Edge.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>


namespace dolos
{

UNITTEST(Vertex, Index)
{
  std::vector<vtx_type> adjncy{1, 3}; 
  std::vector<wgt_type> ewgts{4, 7};

  Edge e0(0, adjncy.data(), ewgts.data());
  Edge e1(1, adjncy.data(), ewgts.data());

  testEqual(e0.index(), static_cast<adj_type>(0));
  testEqual(e1.index(), static_cast<adj_type>(1));
}


UNITTEST(Vertex, Weight)
{
  std::vector<vtx_type> adjncy{1, 3}; 
  std::vector<wgt_type> ewgts{4, 7};

  Edge e0(0, adjncy.data(), ewgts.data());
  Edge e1(1, adjncy.data(), ewgts.data());

  testEqual(e0.weight(), static_cast<wgt_type>(4));
  testEqual(e1.weight(), static_cast<wgt_type>(7));
}

UNITTEST(Vertex, GetVertex)
{
  std::vector<vtx_type> adjncy{1, 3}; 
  std::vector<wgt_type> ewgts{4, 7};

  Edge e0(0, adjncy.data(), ewgts.data());
  Edge e1(1, adjncy.data(), ewgts.data());

  testEqual(e0.destination(), static_cast<vtx_type>(1));
  testEqual(e1.destination(), static_cast<vtx_type>(3));
}

}

