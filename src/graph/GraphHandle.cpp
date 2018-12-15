/**
* @file GraphHandle.cpp
* @brief The GraphHandle class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-11-14
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


#include "GraphHandle.hpp"



namespace poros
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

GraphHandle::GraphHandle(
    sl::ConstArray<adj_type> edgePrefix,
    sl::ConstArray<vtx_type> edgeList,
    sl::ConstArray<wgt_type> vertexWeight,
    sl::ConstArray<wgt_type> edgeWeight) :
  GraphHandle(Graph(std::move(edgePrefix),
                    std::move(edgeList),
                    std::move(vertexWeight),
                    std::move(edgeWeight)))
{
  // do nothing
}

GraphHandle::GraphHandle(
        vtx_type numVertices,
        adj_type numEdges,
        adj_type const * const edgePrefix,
        vtx_type const * const edgeList,
        wgt_type const * const vertexWeight,
        wgt_type const * const edgeWeight) :
  GraphHandle(Graph(numVertices,
                    numEdges,
                    edgePrefix,
                    edgeList,
                    vertexWeight,
                    edgeWeight))
{
  // do nothing
}


GraphHandle::GraphHandle(
    Graph rhs) :
  m_graph(std::make_shared<Graph>(std::move(rhs)))
{
  // do nothing 
}


}
