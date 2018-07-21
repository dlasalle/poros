/**
* @file IStoppingCriteria.hpp
* @brief The IStoppingCriteria interface.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-20
*/


#ifndef DOLOS_SRC_ISTOPPINGCRITERA_HPP
#define DOLOS_SRC_ISTOPPINGCRITERA_HPP

#include "graph/ConstantGraph.hpp"

namespace dolos
{

class IStoppingCriteria
{
  public:
  /**
  * @brief Virtual destructor.
  */
  virtual ~IStoppingCriteria()
  {
    // do nothing
  }

  /**
  * @brief Determine if coarsening should terminate.
  *
  * @param level The level of the coarsest graph.
  * @param fine The fine graph (previous -- may be nullptr).
  * @param coarse The coarse graph (next).
  *
  * @return True if coarseing should stop at the coarse graph.
  */
  virtual bool shouldStop(
      int level,
      ConstantGraph const * fine,
      ConstantGraph const * coarse) const = 0;

};

}


#endif
