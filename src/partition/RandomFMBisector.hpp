/**
* @file RandomFMBisector.hpp
* @brief The RandomFMBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-11-06
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




#ifndef POROS_SRC_RANDOMFMBISECTOR_HPP
#define POROS_SRC_RANDOMFMBISECTOR_HPP


#include "RandomBisector.hpp"
#include "FMRefiner.hpp"
#include "IBisector.hpp"
#include "util/RandomEngineHandle.hpp"


namespace poros
{


class RandomFMBisector :
    public IBisector
{
  public:
    /**
    * @brief Create a new random FM bisector.
    *
    * @param randEngine The random engine.
    */
    RandomFMBisector(
        int maxIterations,
        RandomEngineHandle randEngine);


    /**
    * @brief Virtual destructor.
    */
    virtual ~RandomFMBisector();


    /**
     * @brief Randomly assign vertices to partitions and use FM refinement.
     *
     * @param target The target partitioning to achieve.
     * @param graph The graph.
     *
     * @return The assigned partitioning.
     */
    virtual Partitioning execute(
        TargetPartitioning const * target,
        Graph const * graph) override;


  private:
    RandomBisector m_bisector;  
    FMRefiner m_refiner;
};

}

#endif
