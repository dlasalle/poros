/**
* @file DegreeSortedVertexSet.hpp
* @brief The DegreeSortedVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-23
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

#ifndef POROS_SRC_DEGREESORTEDVERTEXSET_HPP
#define POROS_SRC_DEGREESORTEDVERTEXSET_HPP


#include "graph/PermutedVertexSet.hpp"
#include "graph/VertexSet.hpp"
#include "graph/Graph.hpp"


namespace poros
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
