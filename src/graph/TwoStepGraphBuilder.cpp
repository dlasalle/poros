/**
* @file TwoStepGraphBuilder.cpp
* @brief Implementation of the TwoStepGraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-13
*/



#include "TwoStepGraphBuilder.hpp"
#include "GraphData.hpp"
#include "solidutils/VectorMath.hpp"


namespace dolos
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/


TwoStepGraphBuilder::TwoStepGraphBuilder() :
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


void TwoStepGraphBuilder::setNumVertices(
    vtx_type const numVertices)
{
  ASSERT_EQUAL(m_phase, PHASE_START);

  m_numVertices = numVertices;
}


void TwoStepGraphBuilder::beginVertexPhase()
{
  ASSERT_EQUAL(m_phase, PHASE_START);
  m_phase = PHASE_VERTICES;
  
  // allocate vertex arrays
  m_edgePrefix.assign(m_numVertices+1, 0);;

  m_vertexWeight.resize(m_numVertices);
}


void TwoStepGraphBuilder::beginEdgePhase()
{
  ASSERT_EQUAL(m_phase, PHASE_VERTICES);
  m_phase = PHASE_EDGES;

  // prefix sum edge numbers
  sl::VectorMath::prefixSumExclusive(m_edgePrefix.data(), m_edgePrefix.size());
  m_numEdges = m_edgePrefix[m_numVertices];

  // shift the edgeprefix so that we can insert
  for (vtx_type v = m_numVertices; v > 0; --v) {
    m_edgePrefix[v] = m_edgePrefix[v-1];
  }

  // allocate edge arrays
  m_edgeList.resize(m_numEdges);
  m_edgeWeight.resize(m_numEdges);
}


ConstantGraph TwoStepGraphBuilder::finish()
{
  ASSERT_EQUAL(m_phase, PHASE_EDGES);

  GraphData data(
      std::move(m_edgePrefix),
      std::move(m_edgeList), 
      std::move(m_vertexWeight),
      std::move(m_edgeWeight));
  ConstantGraph graph = data.toGraph();

  m_phase = PHASE_START;

  ASSERT_TRUE(graph.isValid());

  return graph;
}


}
