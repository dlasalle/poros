/**
* @file ContractorFactory.hpp
* @brief The ContractorFactor class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-10-10
*/



#ifndef POROS_SRC_CONTRACTORFACTORY_HPP
#define POROS_SRC_CONTRACTORFACTORY_HPP

#include "IContractor.hpp"
#include "util/TimeKeeper.hpp"

#include <memory>


namespace poros
{

class ContractorFactory
{
  public:
  /**
  * @brief Create a new contractor.
  *
  * @return The instantiated contractor.
  */
  static std::unique_ptr<IContractor> make();

  /**
  * @brief Create a new contractor.
  *
  * @param timeKeeper The time keeper to report times to.
  *
  * @return The instantiated contractor.
  */
  static std::unique_ptr<IContractor> make(
      std::shared_ptr<TimeKeeper> timeKeeper);
  

};



}

#endif
