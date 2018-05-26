/**
* @file BisectionPartitioner_test.cpp
* @brief Unit tests for the BisectionPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-11-08
*/


#include "partition/BisectionPartitioner.hpp"
#include "partition/RandomFMBisector.hpp"
#include "partition/RecursiveBisectionPartitioner.hpp"
#include "util/GridGraphGenerator.hpp"
#include "solidutils/Exception.hpp"
#include "solidutils/UnitTest.hpp"


namespace dolos
{


/******************************************************************************
* UNIT TESTS ******************************************************************
******************************************************************************/

UNITTEST(BisectionPartitioner, ExecuteCorrect)
{
  GridGraphGenerator gen(3,4,5);
  ConstantGraph graph = gen.generate();

  RandomFMBisector rfb(8);
  RecursiveBisectionPartitioner parter(&rfb);
  BisectionPartitioner adapter(&parter);

  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.03);
  
  Partitioning part = adapter.execute(&target, &graph);

  testEqual(part.getNumPartitions(), static_cast<pid_type>(2));
}
  
UNITTEST(BisectionPartitioner, ExecuteInvalid)
{
  GridGraphGenerator gen(3,4,5);
  ConstantGraph graph = gen.generate();

  RandomFMBisector rfb(8);
  RecursiveBisectionPartitioner parter(&rfb);
  BisectionPartitioner adapter(&parter);

  TargetPartitioning target(5, graph.getTotalVertexWeight(), 0.03);
  
  try {
    Partitioning part = adapter.execute(&target, &graph);
    testFail() << "Exception was not thrown.";
  } catch (sl::InvalidInputException const &) {
    // test passed
  }
}
 
 
}
