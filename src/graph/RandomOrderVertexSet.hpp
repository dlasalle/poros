/**
* @file RandomOrderVertexSet.hpp
* @brief The RandomOrderVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-19
*/


#ifndef POROS_SRC_RANDOMORDERVERTEXSET_HPP
#define POROS_SRC_RANDOMORDERVERTEXSET_HPP


#include "graph/PermutedVertexSet.hpp"
#include "graph/VertexSet.hpp"


namespace poros
{

class RandomEngine;

class RandomOrderVertexSet
{
  public:
  /**
  * @brief Create a random order of a given vertex set.
  *
  * @param set The vertex set to traverse in a random order.
  * @param entropyEngine The source of random decisions.
  */
  static PermutedVertexSet generate(
      VertexSet set,
      RandomEngine * randomEngine);


};


}

#endif
