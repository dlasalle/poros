/**
 * @file Graph.hpp
 * @brief The Graph class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#ifndef DOLOS_SRC_GRAPH_HPP
#define DOLOS_SRC_GRAPH_HPP


#include "Base.hpp"

namespace dolos
{

class Graph
{
  public:
    Graph(
        vtx_type nvtxs,
        adj_type nedges,
        adj_type * const edgePrefix = nullptr,
        vtx_type * const edgeList = nullptr,
        wgt_type * const vertexWeight = nullptr,
        wgt_type * const edgeWeight nullptr);

    vtx_type getNumVertices() const;

    adj_type getNumEdges() const;

    adj_type * getEdgePrefix();

    adj_type const * getEdgePrefix() const;

    vtx_type * getEdgeList();

    vtx_type const * getEdgeList() const;

    wgt_type getVertexWeight();

    wgt_type const getVertexWeight() const;

    wgt_type * getEdgeWeight();

    wgt_type const * getEdgeWeight() const;


  private:
    wgt_type m_totalVertexWeight;
    wgt_type m_totalEdgeWeight;

    std::vector<wgt_type> m_vertexWeight;
    std::vector<adj_type> m_edgePrefix;
    std::vector<vtx_type> m_edgeList;
    std::vector<wgt_type> m_edgeWeights;
};

}


#endif
