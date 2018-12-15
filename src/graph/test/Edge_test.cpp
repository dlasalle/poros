/**
* @file Edge_test.cpp
* @brief Unit tests for the Edge class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2018-01-13
*/



#include "graph/Edge.hpp"
#include "solidutils/UnitTest.hpp"

#include <type_traits>


namespace poros
{

UNITTEST(Edge, Index)
{
  Edge e = Edge::make(7);

  testEqual(e.index, 7U);
}

static_assert(std::is_pod<Edge>::value, "Edge must be a POD");
static_assert(sizeof(Edge) == sizeof(adj_type), "Edge be of size scalar.");

}

