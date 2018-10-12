/**
* @file ContractorFactory.cpp
* @brief The implementation of the ContractorFactory class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-10
*/


#include "ContractorFactory.hpp"
#include "SummationContractor.hpp"
#include "TimedContractor.hpp"


namespace dolos
{


/******************************************************************************
* PUBLIC STATIC METHODS *******************************************************
******************************************************************************/

std::unique_ptr<IContractor> ContractorFactory::make()
{
  return std::unique_ptr<IContractor>(new SummationContractor);
}

std::unique_ptr<IContractor> ContractorFactory::make(
    std::shared_ptr<TimeKeeper> timeKeeper)
{
  std::unique_ptr<TimedContractor> ptr(new TimedContractor(make()));

  ptr->setTimeKeeper(timeKeeper);

  return ptr;
}


}
