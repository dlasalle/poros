/**
* @file GraphHandle.cpp
* @brief The GraphHandle class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-11-14
*/


#include "GraphHandle.hpp"



namespace dolos
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
  m_graph(new Graph(std::move(rhs)))
{
  // do nothing 
}


}
