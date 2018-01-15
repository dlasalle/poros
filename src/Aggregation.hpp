/**
* @file Aggregation.hpp
* @brief The Aggregation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/


#ifndef DOLOS_SRC_AGGREGATION_HPP
#define DOLOS_SRC_AGGREGATION_HPP


#include "Base.hpp"
#include <vector>


namespace dolos
{

class Aggregation
{
  public:
    /**
    * @brief Create a new aggregation from a vector. 
    *
    * @param coarseMap The cmap vector.
    * @param numCoarseVertices The number of coarse vertices.
    */
    Aggregation(
        std::vector<vtx_type> && coarseMap,
        vtx_type numCoarseVertices);

  private:
    std::vector<vtx_type> m_coarseMap;
};

}

#endif
