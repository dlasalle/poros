/**
* @file MultiBisector.hpp
* @brief The MultiBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-20
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/



#ifndef POROS_SRC_MULTIBISECTOR_HPP
#define POROS_SRC_MULTIBISECTOR_HPP


#include "IBisector.hpp"

#include <memory>

namespace poros
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
      std::unique_ptr<IBisector> bisector);

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
      Graph const * graph) override;


  private:
  int m_numBisections;
  std::unique_ptr<IBisector> m_bisector;

};

}

#endif
