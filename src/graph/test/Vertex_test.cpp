/**
* @file Vertex_test.cpp
* @brief Unit tests for teh Vertex class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2018-01-13
*/


#include "graph/Vertex.hpp"
#include "solidutils/UnitTest.hpp"

#include <type_traits>



namespace poros
{


UNITTEST(Vertex, Index)
{
  Vertex v = Vertex::make(7);
  
  testEqual(v.index, 7U);
}


static_assert(std::is_pod<Vertex>::value, \
    "Vertex must be trivial.");
static_assert(sizeof(Vertex) == sizeof(vtx_type), \
    "Vertex must be of size scalar.");


}
