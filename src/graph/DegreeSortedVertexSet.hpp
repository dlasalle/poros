/**
* @file DegreeSortedVertexSet.hpp
* @brief The DegreeSortedVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-23
*/

#ifndef DOLOS_SRC_DEGREESORTEDVERTEXSET_HPP
#define DOLOS_SRC_DEGREESORTEDVERTEXSET_HPP


#include "graph/PermutedVertexSet.hpp"
#include "graph/VertexSet.hpp"


namespace dolos
{

class RandomEngine;

class DegreeSortedVertexSet
{
  public:
  /**
  * @brief Produce a set of vertices in ascending order of degree.
  *
  * @param set The vertex set to traverse in a random order.
  */
  static PermutedVertexSet ascending(
      VertexSet set);


  /**
  * @brief Produce a set of vertices in ascending order of degree.
  *
  * @param set The vertex set to traverse in a random order.
  */
  static PermutedVertexSet ascendingRandom(
      VertexSet set,
      RandomEngine * const engine);


};


}

#endif
