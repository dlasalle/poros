/**
* @file OneStepGraphBuilder.hpp
* @brief The OneStepGraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-01-18
*/




#ifndef DOLOS_SRC_ONESTEPGRAPHBUILDER_HPP
#define DOLOS_SRC_ONESTEPGRAPHBUILDER_HPP


#include "graph/GraphHandle.hpp"
#include "Base.hpp"
#include "solidutils/Array.hpp"

#include <vector>


namespace dolos
{


class OneStepGraphBuilder
{
  public:
  /**
  * @brief Create a new graph builder.
  *
  * @param numVertices The number of vertices in the new graph.
  * @param maxNumEdges The maximum number of edges in the coarse graph.
  */
  OneStepGraphBuilder(
      vtx_type numVertices,
      adj_type maxNumEdges);

  /**
  * @brief Add an edge to the current vertex.
  *
  * @param dest The destination of the edge.
  * @param wgt The weight of the edge.
  */
  void addEdge(
      vtx_type const dest,
      wgt_type const wgt)
  {
    adj_type const idx = m_htable[dest];
    if (idx == NULL_ADJ) {
      m_htable[dest] = static_cast<adj_type>(m_numEdges);
      m_edgeList[m_numEdges] = dest;
      m_edgeWeight[m_numEdges] = wgt;
      ++m_numEdges;
    } else {
      m_edgeWeight[idx] += wgt;
    }
  }

  /**
  * @brief Perform bookkeeping for a vertex that will no longer have edges
  * added.
  *
  * @param wgt The weight of the vertex.
  */
  void finishVertex(
      vtx_type wgt);

  /**
  * @brief Build the graph. This resets the builder to its initial state.
  *
  * @return The built graph.
  */
  GraphHandle finish();

  private:
    vtx_type m_numVertices;
    adj_type m_numEdges;
    sl::Array<adj_type> m_edgePrefix;
    sl::Array<vtx_type> m_edgeList;
    sl::Array<wgt_type> m_vertexWeight;
    sl::Array<wgt_type> m_edgeWeight;

    std::vector<adj_type> m_htable;

    // prevent copying
    OneStepGraphBuilder(
        OneStepGraphBuilder const & lhs) = delete;
    OneStepGraphBuilder & operator=(
        OneStepGraphBuilder const & lhs) = delete;



};


}


#endif
