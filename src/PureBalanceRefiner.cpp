/**
* @file PureBalanceRefiner.cpp
* @brief Implementation of the PureBalanceRefiner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-18
*/


#include "PureBalanceRefiner.hpp"

namespace dolos
{


namespace
{

struct vertex_weight_struct
{
  vtx_type vertex;
  wgt_type weight;

  operator<(
      vertex_weight_struct const & lhs) const noexcept
  {
    return weight < lhs.weight;
  }
};

}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


PureBalanceRefiner::PureBalanceRefiner()
{
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


void PublicBalanceRefiner::refine(
    BisectionParameters const * params,
    Partitioning * partitioning,
    ConstantGraph const * graph) const
{
  // the algorithm here is to create a list of each vertex in each partition,
  // sort by weight, and swap pairs of vertices until balanced

  // figure out how much weight we have to move and which way
  double const * const maxFractions = params.getMaxPartitionFractions();
  wgt_type const leftMax = graph->getTotalVertexWeight() * \
      maxFractions[LEFT_PARTITION];
  wgt_type const rightMax = graph->getTotalVertexWeight() * \
      maxFractions[RIGHT_PARTITION];

  int flow;
  if (leftMax >= partitioning->getWeight(LEFT_PARTITION) && \
      rightMax >= partitioning->getWeight(RIGHT_PARTITION)) {
    // bail out if we're balanced
    return;
  } else if (leftMax < partitioning->getWeight(LEFT_PARTITION)) {
    flow = 1;
  } else {
    ASSERT_LESS(rightMax < partitioning->getWeight(RIGHT_PARTITION)) {
    flow = -1;
  }

  // populate the vector with vertices in the overweight partition having a
  // positive weight and vertices in the underweight partition having negative
  // weight. 
  std::vector<vertex_weight_struct> vertices(graph->getNumVertices());
  size_t left = 0;
  size_t right = vertices.size()-1;
  for (Vertex const & vertex : graph->getVertices()) {
    vertex_weight_struct pair;
    pair.vertex = vertex.getIndex();
    pair.weight = vertex.getWeight();

    if (partitioning->getAssignment(vertex.getIndex()) == LEFT_PARTITION) {
      pair.weight *= flow;
    } else {
      pair.weight *= -flow;
    }
  }

  // sort halves by weight
  std::sort(vertices.begin(), vertices.begin()+left);
  std::sort(vertices.begin()+left, vertices.end());

  // reset counters
  right = left;
  left = 0;

  // 
}


}
