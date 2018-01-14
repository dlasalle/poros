/**
* @file Vertex_test.cpp
* @brief Unit tests for teh Vertex class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2018-01-13
*/


#include "Vertex.hpp"
#include "solidutils/UnitTest.hpp"
#include <vector>



namespace dolos
{


UNITTEST(Vertex, Index)
{
  std::vector<wgt_type> vwgts{3, 1};
  std::vector<adj_type> prefix{0, 2, 3};
  std::vector<vtx_type> adjncy{1, 2, 0}; 
  std::vector<wgt_type> ewgts{1, 2, 4};

  Vertex v0(0, vwgts.data(), prefix.data(), adjncy.data(), ewgts.data());
  Vertex v1(1, vwgts.data(), prefix.data(), adjncy.data(), ewgts.data());

  testEqual(v0.index(), 0);
  testEqual(v1.index(), 1);
}


UNITTEST(Vertex, Weight)
{
  std::vector<wgt_type> vwgts{3, 1};
  std::vector<adj_type> prefix{0, 2, 3};
  std::vector<vtx_type> adjncy{1, 2, 0}; 
  std::vector<wgt_type> ewgts{1, 2, 4};

  Vertex v0(0, vwgts.data(), prefix.data(), adjncy.data(), ewgts.data());
  Vertex v1(1, vwgts.data(), prefix.data(), adjncy.data(), ewgts.data());

  testEqual(v0.weight(), 3);
  testEqual(v1.weight(), 1);
}

UNITTEST(Vertex, Degree)
{
  std::vector<wgt_type> vwgts{3, 1};
  std::vector<adj_type> prefix{0, 2, 3};
  std::vector<vtx_type> adjncy{1, 2, 0}; 
  std::vector<wgt_type> ewgts{1, 2, 4};

  Vertex v0(0, vwgts.data(), prefix.data(), adjncy.data(), ewgts.data());
  Vertex v1(1, vwgts.data(), prefix.data(), adjncy.data(), ewgts.data());

  testEqual(v0.degree(), 2);
  testEqual(v1.degree(), 1);
}


}
