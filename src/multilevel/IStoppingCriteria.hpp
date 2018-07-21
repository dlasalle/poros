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


namespace dolos
{

class IStoppringCriteria
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
  * @param fine The fine graph (next).
  * @param coarse The coarse graph (previous -- may be nullptr).
  *
  * @return True if coarseing should stop at the finest graph.
  */
  virtual bool shouldStop(
      ConstantGraph const * fine,
      ConstantGraph const * coarse) = 0;

};

}


#endif
