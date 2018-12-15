/**
* @file FMRefiner.hpp
* @brief The FMRefiner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-19
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



#ifndef POROS_SRC_FMREFINER_HPP
#define POROS_SRC_FMREFINER_HPP


#include "ITwoWayRefiner.hpp"
#include "TargetPartitioning.hpp"


namespace poros
{

/**
* @brief The refiner implementing the Fidducia-Mattheyses algorithm.
*/
class FMRefiner : public ITwoWayRefiner
{
  public:
    /**
    * @brief Create a new FM refiner.
    *
    * @param maxIters The maximum number of refinement iterations.
    * @param maxMoves The maximum number of bad moves to make.
    */
    FMRefiner(
        int maxIters,
        vtx_type maxMoves); 


    /**
    * @brief Perform FM refinement on the bisection.
    *
    * @param params The parameters of the bisection.
    * @param target The target partitioning.
    * @param connectivity The connectivity.
    * @param partitioning The current partitioning.
    * @param graph The graph.
    */
    void refine(
        TargetPartitioning const * target,
        TwoWayConnectivity * connectivity,
        Partitioning * partitioning,
        Graph const * graph);

  private:
    int m_maxRefinementIters;
    vtx_type m_maxMoves;
};

}

#endif
