/**
* @file MultilevelPartioner_test.cpp
* @brief Unit tests for the MultilevelPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-04
*/


#include "partition/MultilevelPartitioner.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/SimpleRandomEngine.hpp"

#include "solidutils/UnitTest.hpp"

namespace dolos
{


UNITTEST(MultilevelPartitioner, ExecuteFullCoarsen8Part)
{
  // build a grid graph
  GridGraphGenerator gen(8, 8, 8);

  // TODO: setup the multilevel partition to contract to 8 coarse vertices

  
}

}
