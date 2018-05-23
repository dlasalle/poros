/**
* @file RandomOrderVertexSet.hpp
* @brief The RandomOrderVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-19
*/


#ifndef DOLOS_SRC_RANDOMORDERVERTEXSET_HPP
#define DOLOS_SRC_RANDOMORDERVERTEXSET_HPP


#include "PermutedVertexSet.hpp"
#include "VertexSet.hpp"
#include "IRandomEngine.hpp"


namespace dolos
{

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
      IRandomEngine * randomEngine);


};


}

#endif
