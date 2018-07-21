/**
* @file CompositeStoppingCriteria.hpp
* @brief The CompositeStoppingCriteria class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-21
*/

#ifndef DOLOS_SRC_COMPOSITESTOPPINGCRITERIA_HPP
#define DOLOS_SRC_COMPOSITESTOPPINGCRITERIA_HPP


#include "IStoppingCriteria.hpp"

#include <memory>
#include <vector>

namespace dolos
{

class CompositeStoppingCriteria : public IStoppingCriteria
{
  public:
  /**
  * @brief Create a new composite stopping criteria.
  */
  CompositeStoppingCriteria();

  /**
  * @brief Add criteria for stopping.
  *
  * @param criteria The criteria.
  */
  void addCriteria(
      std::unique_ptr<IStoppingCriteria> criteria);

  /**
  * @brief Determine if coarsening should terminate.
  *
  * @param level The level of the coarsest graph.
  * @param fine The fine graph (previous -- may be nullptr).
  * @param coarse The coarse graph (next).
  *
  * @return True if coarseing should stop at the coarse graph.
  */
  bool shouldStop(
      int level,
      ConstantGraph const * fine,
      ConstantGraph const * coarse) const override;

  private:
  std::vector<std::unique_ptr<IStoppingCriteria>> m_criteria;

};

}

#endif
