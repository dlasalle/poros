/**
* @file OneStepGraphBuilder.hpp
* @brief The OneStepGraphBuilder class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-01-18
*/




#ifndef DOLOS_SRC_ONESTEPGRAPHBUILDER_HPP
#define DOLOS_SRC_ONESTEPGRAPHBUILDER_HPP


#include "graph/ConstantGraph.hpp"
#include "Base.hpp"
#include "solidutils/Array.hpp"


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
  * @brief Add a vertex to this graph.
  *
  * @param weight The weight of the new vertex.
  * @param degree The degree of the new vertex.
  * @param neighbors The neighbors of the this vertex.
  * @param edgeWeights The weight of edges connecting vertices.
  */
  void addVertex(
      wgt_type weight,
      vtx_type degree,
      vtx_type const * neighbors,
      wgt_type const * edgeWeights);


  /**
  * @brief Build the graph. This resets the builder to its initial state.
  *
  * @return The built graph.
  */
  ConstantGraph finish();

  private:
    vtx_type m_numVertices;
    adj_type m_numEdges;
    sl::Array<adj_type> m_edgePrefix;
    sl::Array<vtx_type> m_edgeList;
    sl::Array<wgt_type> m_vertexWeight;
    sl::Array<wgt_type> m_edgeWeight;

    // prevent copying
    OneStepGraphBuilder(
        OneStepGraphBuilder const & lhs) = delete;
    OneStepGraphBuilder & operator=(
        OneStepGraphBuilder const & lhs) = delete;



};


}

#endif