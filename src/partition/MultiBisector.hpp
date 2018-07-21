/**
* @file MultiBisector.hpp
* @brief The MultiBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-20
*/



#ifndef DOLOS_SRC_MULTIBISECTOR_HPP
#define DOLOS_SRC_MULTIBISECTOR_HPP


#include "IBisector.hpp"


namespace dolos
{


class MultiBisector : public IBisector
{
  public:
  /**
  * @brief Create a new multibiesctor object.
  *
  * @param numBisections The number of bisections to make.
  * @param bisector The bisector to use.
  */
  MultiBisector(
      int numBisections,
      IBisector * bisector);

  /**
  * @brief Deleted copy constructor.
  *
  * @param lhs The bisector to copy.
  */
  MultiBisector(
      MultiBisector& lhs) = delete;

  /**
  * @brief Deleted copy assignment operator.
  *
  * @param lhs The bisector to assign.
  *
  * @return This bisector.
  */
  MultiBisector operator=(
      MultiBisector& lhs) = delete;


  /**
  * @brief Virtual destructor.
  */
  virtual ~MultiBisector();


  /**
  * @brief Create a new bisection.
  *
  * @param target The target bisection.
  * @param graph The graph.
  *
  * @return The best bisection created.
  */
  virtual Partitioning execute(
      TargetPartitioning const * target,
      ConstantGraph const * graph) override;


  private:
  int m_numBisections;
  IBisector * m_bisector;

};

}

#endif
