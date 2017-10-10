/**
* @file ConstantGraph.cpp
* @brief The implementation of the ConstantGraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/



#include "Base.hpp"
#include "ConstantGraph.hpp"


namespace dolos
{


ConstantGraph::ConstantGraph(
    vtx_type nvtxs,
    adj_type nedges,
    adj_type const * const edgePrefix,
    vtx_type const * const edgeList,
    wgt_type const * const vertexWeight,
    wgt_type const * const edgeWeight) :
  m_numVertices(nvtxs),
  m_numEdges(nedges),
  m_totalVertexWeight(0),
  m_totalEdgeWeight(0),
  m_vertexWeight(nvtxs, vertexWeight),
  m_edgePrefix(nvtxs+1, edgePrefix),
  m_edgeList(nedges, edgeList),
  m_edgeWeight(nedges, edgeWeight)
{
  if (vertexWeight == nullptr) {
    m_vertexWeight = ConstantArray<wgt_type>(nvtxs, 1);
  }

  if (edgeWeight == nullptr) {
    m_edgeWeight = ConstantArray<wgt_type>(nedges, 1);
  }
}


ConstantGraph::ConstantGraph(
    ConstantGraph && lhs) :
{
  
}


}
