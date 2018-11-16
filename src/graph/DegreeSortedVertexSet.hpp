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
#include "graph/Graph.hpp"


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
      VertexSet const set,
      Graph const * const graph);


  /**
  * @brief Produce a set of vertices in ascending order of degree.
  *
  * @param set The vertex set to traverse in a random order.
  */
  static PermutedVertexSet ascendingRandom(
      VertexSet set,
      Graph const * const graph,
      RandomEngine * const engine);


};


}

#endif
