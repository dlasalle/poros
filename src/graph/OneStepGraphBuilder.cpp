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

#include <algorithm>

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
  m_edgePrefix(numVertices+1),
  m_edgeList(maxNumEdges),
  m_vertexWeight(numVertices),
  m_edgeWeight(maxNumEdges),
  m_htable(numVertices, NULL_ADJ)
{
  m_edgePrefix[0] = 0;
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void OneStepGraphBuilder::finishVertex(
      vtx_type const vertexWeight)
{
  vtx_type const thisVtx = m_numVertices;

  ++m_numVertices;

  adj_type const start = m_edgePrefix[thisVtx];
  for (vtx_type j = start; j < m_numEdges; ++j) {
    vtx_type const u = m_edgeList[j];
    ASSERT_LESS(u, m_htable.size());
    m_htable[u] = NULL_ADJ;
  }

  m_vertexWeight[thisVtx] = vertexWeight;
  m_edgePrefix[m_numVertices] = m_numEdges;
}


GraphHandle OneStepGraphBuilder::finish()
{
  m_edgeList.shrink(m_numEdges);
  m_edgeWeight.shrink(m_numEdges);

  GraphHandle handle(
      std::move(m_edgePrefix),
      std::move(m_edgeList),
      std::move(m_vertexWeight),
      std::move(m_edgeWeight));

  ASSERT_TRUE(handle->isValid());

  return handle;
}



}

