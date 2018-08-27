/**
* @file RandomFMBisector.hpp
* @brief The RandomFMBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-11-06
*/




#ifndef DOLOS_SRC_RANDOMFMBISECTOR_HPP
#define DOLOS_SRC_RANDOMFMBISECTOR_HPP


#include "RandomBisector.hpp"
#include "FMRefiner.hpp"
#include "IBisector.hpp"
#include "util/RandomEngineHandle.hpp"


namespace dolos
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
        ConstantGraph const * graph) override;


  private:
    RandomBisector m_bisector;  
    FMRefiner m_refiner;
};

}

#endif
