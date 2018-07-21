/**
* @file EdgeRatioStoppingCriteria.hpp
* @brief The EdgeRatioStoppingCriteria class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-20
*/


#ifndef DOLOS_SRC_EDGERATIOSTOPPINGCRITERIA_HPP
#define DOLOS_SRC_EDGERATIOSTOPPINGCRITERIA_HPP

#include "graph/ConstantGraph.hpp"
#include "multilevel/IStoppingCriteria.hpp"

namespace dolos
{

class EdgeRatioStoppingCriteria : public IStoppingCriteria
{
  public:
  /**
  * @brief Create a new EdgeRatioStoppingCriteria.
  *
  * @param ratio The ratio at which to stop coarsening.
  */
  EdgeRatioStoppingCriteria(
      double ratio);

  /**
  * @brief Determine if coarsening should terminate based on the ratio of the
  * fine and coarse graphs.
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
  double m_ratio;
};




}

#endif
