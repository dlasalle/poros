/**
* @file RandomOrderVertexSet.cpp
* @brief Implementation of the RandomOrderVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-21
*/

#include "RandomOrderVertexSet.hpp"
#include "util/RandomEngine.hpp"

namespace dolos
{


/******************************************************************************
* PUBLIC STATIC METHODS *******************************************************
******************************************************************************/

PermutedVertexSet RandomOrderVertexSet::generate(
    VertexSet const set,
    RandomEngine * const randomEngine)
{
  vtx_type const numVertices = set.size();
  std::unique_ptr<vtx_type[]> perm(new vtx_type[numVertices]);

  randomEngine->fillWithPerm(perm.get(), 0, numVertices);

  return PermutedVertexSet(std::move(perm), numVertices);
}


}
