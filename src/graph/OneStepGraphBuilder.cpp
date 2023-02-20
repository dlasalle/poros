/**
* @file OneStepGraphBuilder.cpp
* @brief Implementation of the OneStepGraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-20
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



#include "OneStepGraphBuilder.hpp"
#include "solidutils/Debug.hpp"

#include <algorithm>

namespace poros
{



/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

OneStepGraphBuilder::OneStepGraphBuilder(
    vtx_type const numVertices,
    adj_type const maxNumEdges) :
  m_numVertices(0),
  m_numEdges(1), // implicit self loop
  m_edgePrefix(numVertices+1),
  m_edgeList(maxNumEdges+1), // last slot used for self loops
  m_vertexWeight(numVertices),
  m_edgeWeight(maxNumEdges+1), // last slot used for self loops
  m_totalVertexWeight(0),
  m_totalEdgeWeight(0),
  m_htable(numVertices+1, NULL_ADJ),
  m_maxNumEdges(maxNumEdges)
{
  m_edgePrefix[0] = 0;

  // add implicit first edge 
  m_htable[0] = 0;
  m_edgeList[0] = 0;
  m_edgeWeight[0] = 0;
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

GraphHandle OneStepGraphBuilder::finish()
{
  // delete last self loop
  --m_numEdges;

  m_edgeList.shrink(m_numEdges);
  m_edgeWeight.shrink(m_numEdges);

  GraphHandle handle(Graph(
      std::move(m_edgePrefix),
      std::move(m_edgeList),
      std::move(m_vertexWeight),
      std::move(m_edgeWeight),
      m_totalVertexWeight,
      m_totalEdgeWeight,
      false,
      false));

  ASSERT_TRUE(handle->isValid());

  return handle;
}



}

