/**
* @file ConstantGraph_test.cpp
* @brief Unit tests for the ConstantGraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-11
*/


#include "ConstantGraph.hpp"
#include "DomTest.hpp"
#include "GridGraphGenerator.hpp"


namespace dolos
{


UNITTEST(ConstantGraph, IterateVertices)
{
  GridGraphGenerator gen(5, 5, 5);

  ConstantGraph g = gen.generate();


}


}
