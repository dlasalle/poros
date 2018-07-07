/**
 * @file RandomBisector.cpp
 * @brief Implementation of RandomParittioner. 
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#include "RandomBisector.hpp"
#include "PartitioningAnalyzer.hpp"
#include "graph/RandomOrderVertexSet.hpp"
#include <algorithm>


namespace dolos
{


/******************************************************************************
* HELPER FUNCTIONS ************************************************************
******************************************************************************/

namespace
{

struct vertex_struct
{
  vtx_type vertex; 
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
    ConstantGraph const * const graph)
{
  std::vector<vertex_struct> vertices(graph->numVertices());

  size_t left = 0;
  size_t right = vertices.size()-1;
  for (Vertex const & vertex : graph->vertices()) {
    vertex_struct pair;
    pair.vertex = vertex.index();
    pair.weight = vertex.weight();

    if (partitioning->getAssignment(pair.vertex) == LEFT_PARTITION) {
      vertices[left] = pair;
      ++left;
    } else {
      vertices[right] = pair;
      --right;
    }
  }
  ASSERT_EQUAL(left, right+1);

  // sort
  std::sort(vertices.begin(), vertices.begin()+left);
  std::sort(vertices.begin()+left, vertices.end());

  // how much weight we need to fix
  wgt_type const minDelta = \
      partitioning->getWeight(RIGHT_PARTITION) - maxRightWeight;
  wgt_type const maxDelta = \
      maxLeftWeight - partitioning->getWeight(LEFT_PARTITION);

  // reset pointers -- start the heaviest right-side vertex and lightest
  // left-side vertex
  size_t const middle = left;
  right = vertices.size()-1;
  left = 0;

  wgt_type const weight = vertices[right].weight;

  wgt_diff_type const minOffset = weight - maxDelta;
  wgt_diff_type const maxOffset = weight - minDelta;

  // binary search the left array for the right weight vertex to swap with
  std::vector<vertex_struct>::iterator lower = \
      std::lower_bound(vertices.begin(), vertices.begin()+middle, minOffset);
  std::vector<vertex_struct>::iterator upper = \
      std::lower_bound(vertices.begin(), vertices.begin()+middle, maxOffset);

  if (lower <= upper) {
    // perform swap
    partitioning->move(vertices[right].vertex, LEFT_PARTITION);
    partitioning->move((*lower).vertex, RIGHT_PARTITION);
  }
}

}


/******************************************************************************
* CONSTRUCTORS ****************************************************************
******************************************************************************/

RandomBisector::RandomBisector(
    IRandomEngine * const randEngine) :
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
    ConstantGraph const * const graph) const
{
  // random vertex order

  // start with all vertices in the right partition
  Partitioning partitioning(NUM_BISECTION_PARTS, graph);
  partitioning.assignAll(RIGHT_PARTITION);

  PartitioningAnalyzer analyzer(&partitioning, target);

  PermutedVertexSet vertices = RandomOrderVertexSet::generate(
      graph->vertices(), m_randEngine);

  for (Vertex const vertex : vertices) {
    // balance to within 1 vertex
    if (partitioning.getWeight(LEFT_PARTITION) + vertex.weight() > \
        target->getMaxWeight(LEFT_PARTITION)) {
      break;
    }

    double const balance = analyzer.calcMaxImbalance();

    partitioning.move(vertex.index(), LEFT_PARTITION);

    if (balance < analyzer.calcMaxImbalance()) {
      // we hit the best balance undo move and exit loop 
      partitioning.move(vertex.index(), RIGHT_PARTITION);
      break;
    }
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
