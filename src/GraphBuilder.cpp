/**
* @file GraphBuilder.cpp
* @brief Implementation of the GraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-13
*/



#include "GraphBuilder.hpp"
#include "GraphData.hpp"
#include "ArrayUtils.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


GraphBuilder::GraphBuilder() :
  m_phase(PHASE_START),
  m_numVertices(0),
  m_numEdges(0),
  m_edgePrefix(0),
  m_edgeList(0),
  m_vertexWeight(0),
  m_edgeWeight(0)
{
  // do nothing
}





/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/


void GraphBuilder::setNumVertices(
    vtx_type const numVertices)
{
  ASSERT_EQUAL(m_phase, PHASE_START);

  m_numVertices = numVertices;
}


void GraphBuilder::beginVertexPhase()
{
  ASSERT_EQUAL(m_phase, PHASE_START);
  m_phase = PHASE_VERTICES;
  
  // allocate vertex arrays
  m_edgePrefix.resize(m_numVertices+1);
  m_edgePrefix.set(0);

  m_vertexWeight.resize(m_numVertices);
}


void GraphBuilder::beginEdgePhase()
{
  ASSERT_EQUAL(m_phase, PHASE_VERTICES);
  m_phase = PHASE_EDGES;

  // prefix sum edge numbers
  solidutils::ArrayUtils::prefixSumExclusive(&m_edgePrefix);
  m_numEdges = m_edgePrefix[m_numVertices];

  // shift the edgeprefix so that we can insert
  for (vtx_type v = m_numVertices; v > 0; --v) {
    m_edgePrefix[v] = m_edgePrefix[v-1];
  }

  // allocate edge arrays
  m_edgeList.resize(m_numEdges);
  m_edgeWeight.resize(m_numEdges);
}


ConstantGraph GraphBuilder::finish()
{
  ASSERT_EQUAL(m_phase, PHASE_EDGES);

  GraphData data(&m_edgePrefix, &m_edgeList, &m_vertexWeight, &m_edgeWeight);
  ConstantGraph graph = data.toGraph();

  m_phase = PHASE_START;

  return graph;
}


}
