/**
* @file CompositeStoppingCriteria_test.cpp
* @brief Unit tests for the CompositeStoppingCriteria class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-21
*/

#include "multilevel/CompositeStoppingCriteria.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "solidutils/UnitTest.hpp"

namespace dolos
{


/******************************************************************************
* MOCK CLASSES ****************************************************************
******************************************************************************/

namespace
{

class FalseStoppingCriteria : public IStoppingCriteria
{
  bool shouldStop(
      int,
      ConstantGraph const *,
      ConstantGraph const *) const override
  {
    return false;
  }
};

class TrueStoppingCriteria : public IStoppingCriteria
{
  bool shouldStop(
      int,
      ConstantGraph const *,
      ConstantGraph const *) const override
  {
    return true;
  }
};

}


/******************************************************************************
* UNIT TESTS ******************************************************************
******************************************************************************/

UNITTEST(CompositeStoppingCriteria, Empty)
{
  // graph with 144 edges
  GridGraphGenerator genFine(4, 4, 4);
  ConstantGraph fine = genFine.generate();

  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  ConstantGraph coarse = genCoarse.generate();
  
  CompositeStoppingCriteria criteria;

  testFalse(criteria.shouldStop(1, &fine, &coarse));
  testFalse(criteria.shouldStop(1, &fine, &fine));
  testFalse(criteria.shouldStop(0, nullptr, &fine));
}

UNITTEST(CompositeStoppingCriteria, ShouldContinue)
{
  // graph with 144 edges
  GridGraphGenerator genFine(4, 4, 4);
  ConstantGraph fine = genFine.generate();

  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  ConstantGraph coarse = genCoarse.generate();
  
  CompositeStoppingCriteria criteria;

  criteria.add(
    std::unique_ptr<IStoppingCriteria>(new FalseStoppingCriteria));
  criteria.add(
    std::unique_ptr<IStoppingCriteria>(new FalseStoppingCriteria));

  testFalse(criteria.shouldStop(1, &fine, &coarse));
}


UNITTEST(CompositeStoppingCriteria, ShouldStop)
{
  // graph with 144 edges
  GridGraphGenerator genFine(4, 4, 4);
  ConstantGraph fine = genFine.generate();

  // graph with 108 edges
  GridGraphGenerator genCoarse(16, 4, 1);
  ConstantGraph coarse = genCoarse.generate();

  CompositeStoppingCriteria criteria;

  criteria.add(
    std::unique_ptr<IStoppingCriteria>(new FalseStoppingCriteria));
  criteria.add(
    std::unique_ptr<IStoppingCriteria>(new TrueStoppingCriteria));

  testTrue(criteria.shouldStop(1, &fine, &coarse));
}

}
