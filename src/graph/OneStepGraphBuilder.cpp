/**
* @file OneStepGraphBuilder.cpp
* @brief Implementation of the OneStepGraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-20
*/



#include "OneStepGraphBuilder.hpp"
#include "solidutils/Debug.hpp"
#include "GraphData.hpp"


namespace dolos
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

OneStepGraphBuilder::OneStepGraphBuilder(
    vtx_type const numVertices,
    adj_type const maxNumEdges) :
  m_numVertices(0),
  m_numEdges(0),
  m_edgePrefix(numVertices+1, 0),
  m_edgeList(maxNumEdges),
  m_vertexWeight(numVertices),
  m_edgeWeight(maxNumEdges)
{
  // do nothing 
}




/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void OneStepGraphBuilder::addVertex(
    wgt_type const weight,
    vtx_type const degree,
    vtx_type const * const neighbors,
    wgt_type const * const edgeWeights)
{
  m_vertexWeight[m_numVertices] = weight;
  for (vtx_type i = 0; i < degree; ++i) {
    ASSERT_LESS(m_numEdges, m_edgeList.size());
    m_edgeList[m_numEdges] = neighbors[i];
    ASSERT_LESS(m_numEdges, m_edgeWeight.size());
    m_edgeWeight[m_numEdges] = edgeWeights[i]; 
    ++m_numEdges;
  }
  ++m_numVertices;
  m_edgePrefix[m_numVertices] = m_numEdges;
}


ConstantGraph OneStepGraphBuilder::finish()
{
  ASSERT_EQUAL(m_numVertices, m_vertexWeight.size());

  m_edgePrefix.resize(m_numVertices+1);
  m_edgeList.resize(m_numEdges);
  m_vertexWeight.resize(m_numVertices);
  m_edgeWeight.resize(m_numEdges);

  GraphData data(&m_edgePrefix, &m_edgeList, &m_vertexWeight, &m_edgeWeight);
  ConstantGraph graph = data.toGraph();

  return graph;

}



}

