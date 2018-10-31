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

#include <algorithm>

namespace dolos
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

OneStepGraphBuilder::OneStepGraphBuilder(
    vtx_type const numVertices,
    adj_type const maxNumEdges) :
  m_edgePrefix(1, 0),
  m_edgeList(),
  m_vertexWeight(),
  m_edgeWeight(),
  m_htable(numVertices, NULL_ADJ)
{
  m_edgePrefix.reserve(numVertices+1);
  m_edgeList.reserve(maxNumEdges);
  m_vertexWeight.reserve(numVertices);
  m_edgeWeight.reserve(maxNumEdges);
}




/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void OneStepGraphBuilder::finishVertex(
      vtx_type const vertexWeight)
{
  adj_type const loopIdx = m_htable[m_vertexWeight.size()];
  if (loopIdx != NULL_ADJ) {
    // pop out self loop
    m_edgeList[loopIdx] = m_edgeList.back();
    m_edgeList.pop_back();
    m_edgeWeight[loopIdx] = m_edgeWeight.back();
    m_edgeWeight.pop_back();
    m_htable[m_vertexWeight.size()] = NULL_ADJ;
  }

  adj_type const start = m_edgePrefix[m_vertexWeight.size()];
  adj_type const end = m_edgeList.size(); 
  for (vtx_type j = start; j < end; ++j) {
    vtx_type const u = m_edgeList[j];
    ASSERT_LESS(u, m_htable.size());
    m_htable[u] = NULL_ADJ;
  }

  m_edgePrefix.emplace_back(end);
  m_vertexWeight.emplace_back(vertexWeight);
}


ConstantGraph OneStepGraphBuilder::finish()
{
  ASSERT_EQUAL(m_edgePrefix.size(), m_vertexWeight.size()+1);

  GraphData data(
      std::move(m_edgePrefix),
      std::move(m_edgeList),
      std::move(m_vertexWeight),
      std::move(m_edgeWeight));
  ConstantGraph graph = data.toGraph();

  ASSERT_TRUE(graph.isValid());

  return graph;
}



}

