/**
* @file DegreeSortedVertexSet.cpp
* @brief Implementation of the DegreeSortedVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-23
*/


#include "DegreeSortedVertexSet.hpp"
#include "graph/Graph.hpp"
#include "util/RandomEngine.hpp"
#include "solidutils/Sort.hpp"


namespace dolos
{

/******************************************************************************
* PUBLIC STATIC METHODS *******************************************************
******************************************************************************/

PermutedVertexSet DegreeSortedVertexSet::ascending(
    VertexSet const set,
    Graph const * const graph)
{
  vtx_type const numVertices = set.size();
  sl::Array<vtx_type> degrees(numVertices);
  for (Vertex const & vertex : set) {
    degrees[vertex.index] = graph->degreeOf(vertex);
  }

  std::unique_ptr<vtx_type[]> perm = sl::Sort::fixedKeys<vtx_type, vtx_type>( \
      degrees.data(), degrees.size());

  return PermutedVertexSet(std::move(perm), numVertices);  
}


PermutedVertexSet DegreeSortedVertexSet::ascendingRandom(
    VertexSet const set,
    Graph const * const graph,
    RandomEngine * const engine)
{
  vtx_type const numVertices = set.size();
  sl::Array<vtx_type> degrees(numVertices);
  for (Vertex const & vertex : set) {
    degrees[vertex.index] = graph->degreeOf(vertex);
  }

  std::unique_ptr<vtx_type[]> perm = \
      sl::Sort::fixedKeysRandom<vtx_type, vtx_type>( \
      degrees.data(), degrees.size(), *engine);

  return PermutedVertexSet(std::move(perm), numVertices);
}

}
