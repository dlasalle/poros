/**
 * @file RandomBisector.cpp
 * @brief Implementation of RandomParittioner. 
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018
 * @version 1
 * @date 2017-10-04
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


#include "RandomBisector.hpp"
#include "PartitioningAnalyzer.hpp"
#include "graph/RandomOrderVertexSet.hpp"

#include "solidutils/Array.hpp"

#include <algorithm>


namespace poros
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{

struct vertex_struct
{
  Vertex vertex; 
  wgt_type weight;

  bool operator<(
      vertex_struct const & lhs) const noexcept
  {
    return weight < lhs.weight;
  }


  bool operator<(
      wgt_type const weight) const noexcept
  {
    return this->weight < weight;
  }
 

  bool operator<=(
      wgt_type const weight) const noexcept
  {
    return this->weight <= weight;
  }


  bool operator>(
      wgt_type const weight) const noexcept
  {
    return this->weight > weight;
  }
 
    
};


template<bool HAS_VERTEX_WEIGHTS>
size_t fillVertexWeightPairs(
    Graph const * const graph,
    Partitioning const * const part,
    vertex_struct * const vertices)
{
  size_t left = 0;
  size_t right = graph->numVertices()-1;

  for (Vertex const vertex : graph->vertices()) {
    vertex_struct pair;
    pair.vertex = vertex;
    pair.weight = graph->weightOf<HAS_VERTEX_WEIGHTS>(vertex);

    if (part->getAssignment(pair.vertex) == LEFT_PARTITION) {
      vertices[left] = pair;
      ++left;
    } else {
      vertices[right] = pair;
      --right;
    }
  }
  ASSERT_EQUAL(left, right+1);

  // sort
  std::sort(vertices, vertices + left);
  std::sort(vertices+left, vertices + graph->numVertices());

  return left;
}

/**
* @brief Swap vertices to achieve balance where the right side is overweight.
*
* @param maxLeftWeight The maximum weight of the left partition.
* @param maxRightWeight The maximum weight of the right partition.
* @param partitioning The partitioning.
* @param graph The graph.
*/
void swapBalanceRight(
    wgt_type const maxLeftWeight,
    wgt_type const maxRightWeight,
    Partitioning * const partitioning,
    Graph const * const graph)
{
  sl::Array<vertex_struct> vertices(graph->numVertices());

  size_t left;
  if (graph->hasUnitVertexWeight()) {
    left = fillVertexWeightPairs<false>(graph, partitioning, vertices.data());
  } else {
    left = fillVertexWeightPairs<true>(graph, partitioning, vertices.data());
  }

  // how much weight we need to fix
  wgt_diff_type const minDelta = \
      partitioning->getWeight(RIGHT_PARTITION) - maxRightWeight;
  wgt_diff_type const maxDelta = \
      maxLeftWeight - partitioning->getWeight(LEFT_PARTITION);

  // reset pointers -- start the heaviest right-side vertex and lightest
  // left-side vertex
  size_t const middle = left;
  size_t const right = vertices.size()-1;
  left = 0;

  wgt_diff_type const weight = vertices[right].weight;

  wgt_diff_type const minOffset = weight - maxDelta;
  wgt_diff_type const maxOffset = weight - minDelta;

  // binary search the left array for the right weight vertex to swap with
  sl::Array<vertex_struct>::const_iterator lower = \
      std::lower_bound(vertices.begin(), vertices.begin()+middle, minOffset);
  sl::Array<vertex_struct>::const_iterator upper = \
      std::lower_bound(vertices.begin(), vertices.begin()+middle, maxOffset);

  // if we found such a vertice
  if (lower < upper) {
    // perform swap
    partitioning->move(vertices[right].vertex, LEFT_PARTITION);
    partitioning->move((*lower).vertex, RIGHT_PARTITION);
  }
}


template<bool HAS_VERTEX_WEIGHTS>
void fillLeft(
    TargetPartitioning const * const target,
    Graph const * const graph,
    PermutedVertexSet const vertices,
    Partitioning * const part)
{
  PartitioningAnalyzer analyzer(part, target);

  for (Vertex const vertex : vertices) {
    // balance to within 1 vertex
    if (part->getWeight(LEFT_PARTITION) + \
        graph->weightOf<HAS_VERTEX_WEIGHTS>(vertex) > \
        target->getMaxWeight(LEFT_PARTITION)) {
      break;
    }

    double const balance = analyzer.calcMaxImbalance();

    part->move(vertex, LEFT_PARTITION);

    if (balance < analyzer.calcMaxImbalance()) {
      // we hit the best balance undo move and exit loop 
      part->move(vertex, RIGHT_PARTITION);
      break;
    }
  }
}

}


/******************************************************************************
* CONSTRUCTORS ****************************************************************
******************************************************************************/

RandomBisector::RandomBisector(
    RandomEngineHandle randEngine) :
  m_randEngine(randEngine)
{
  // do nothing
}

RandomBisector::~RandomBisector()
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Partitioning RandomBisector::execute(
    TargetPartitioning const * const target,
    Graph const * const graph)
{
  // random vertex order

  // start with all vertices in the right partition
  Partitioning partitioning(NUM_BISECTION_PARTS, graph);
  partitioning.assignAll(RIGHT_PARTITION);

  PermutedVertexSet vertices = RandomOrderVertexSet::generate(
      graph->vertices(), m_randEngine.get());

  if (graph->hasUnitVertexWeight()) {
    fillLeft<false>(target, graph, std::move(vertices), &partitioning);
  } else {
    fillLeft<true>(target, graph, std::move(vertices), &partitioning);
  }

  // by construction the left partition cannot be overweight at this point
  ASSERT_LESSEQUAL(partitioning.getWeight(LEFT_PARTITION), \
      target->getMaxWeight(LEFT_PARTITION));
  if (partitioning.getWeight(RIGHT_PARTITION) > \
      target->getMaxWeight(RIGHT_PARTITION)) {

    // if the right partition is still overweight try to find a pair two swap 
    swapBalanceRight(target->getMaxWeight(LEFT_PARTITION), \
        target->getMaxWeight(RIGHT_PARTITION), &partitioning, graph);
  }

  partitioning.recalcCutEdgeWeight();

  return partitioning;
}


}
