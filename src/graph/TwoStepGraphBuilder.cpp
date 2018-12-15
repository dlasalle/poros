/**
* @file TwoStepGraphBuilder.cpp
* @brief Implementation of the TwoStepGraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-13
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



#include "TwoStepGraphBuilder.hpp"
#include "solidutils/VectorMath.hpp"


namespace poros
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
  m_edgePrefix = sl::Array<adj_type>(m_numVertices+1, 0);
  m_vertexWeight = sl::Array<wgt_type>(m_numVertices);
}


void TwoStepGraphBuilder::beginEdgePhase()
{
  ASSERT_EQUAL(m_phase, PHASE_VERTICES);
  m_phase = PHASE_EDGES;

  // prefix sum edge numbers
  sl::VectorMath::prefixSumExclusive(m_edgePrefix.begin(), m_edgePrefix.end());
  m_numEdges = m_edgePrefix[m_numVertices];

  // shift the edgeprefix so that we can insert
  for (vtx_type v = m_numVertices; v > 0; --v) {
    m_edgePrefix[v] = m_edgePrefix[v-1];
  }

  // allocate edge arrays
  m_edgeList = sl::Array<vtx_type>(m_numEdges);
  m_edgeWeight = sl::Array<wgt_type>(m_numEdges);
}


GraphHandle TwoStepGraphBuilder::finish()
{
  ASSERT_EQUAL(m_phase, PHASE_EDGES);

  GraphHandle handle(
      std::move(m_edgePrefix),
      std::move(m_edgeList), 
      std::move(m_vertexWeight),
      std::move(m_edgeWeight));

  m_phase = PHASE_START;

  ASSERT_TRUE(handle->isValid());

  return handle;
}


}
