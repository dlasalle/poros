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


#include "graph/ConstantGraph.hpp"
#include "Base.hpp"

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

  void addEdge(
      vtx_type const dest,
      wgt_type const wgt)
  {
    adj_type const idx = m_htable[dest];
    if (idx == NULL_ADJ) {
      m_htable[dest] = static_cast<adj_type>(m_edgeList.size());
      m_edgeList.emplace_back(dest);
      m_edgeWeight.emplace_back(wgt);
    } else {
      m_edgeWeight[idx] += wgt;
    }
  }

  void finishVertex(
      vtx_type wgt);

  /**
  * @brief Build the graph. This resets the builder to its initial state.
  *
  * @return The built graph.
  */
  ConstantGraph finish();

  private:
    std::vector<adj_type> m_edgePrefix;
    std::vector<vtx_type> m_edgeList;
    std::vector<wgt_type> m_vertexWeight;
    std::vector<wgt_type> m_edgeWeight;
    std::vector<adj_type> m_htable;

    // prevent copying
    OneStepGraphBuilder(
        OneStepGraphBuilder const & lhs) = delete;
    OneStepGraphBuilder & operator=(
        OneStepGraphBuilder const & lhs) = delete;



};


}

#endif
