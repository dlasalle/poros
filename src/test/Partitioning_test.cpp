/**
* @file Partitioning_test.cpp
* @brief Unit tests for the partitioning class. 
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-05
*/

#include "DomTest.hpp"
#include "Partitioning.hpp"


namespace dolos
{

UNITTEST(Partitioning, NumberOfPartitions)
{
  Partitioning p(5, 100);

  testEquals(5, p.getNumPartitions());
}

}
