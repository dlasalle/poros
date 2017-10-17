/**
* @file Subgraph.hpp
* @brief The Subgraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/




#ifndef DOLOS_SRC_SUBGRAPH_HPP
#define DOLOS_SRC_SUBGRAPH_HPP


#include "ConstantGraph.hpp"
#include "Array.hpp"



namespace dolos
{

class Subgraph
{
  public:
    /**
    * @brief Create a new subgraph.
    *
    * @param superGraph The super graph.
    * @param superMap The mapping of vertices to the super graph.
    */
    Subgraph(
        ConstantGraph * graph,
        Array<vtx_type> * superMap);


    /**
    * @brief Get the underlying graph.
    *
    * @return The graph.
    */
    ConstantGraph const * getGraph() const;


    /**
    * @brief Get the mapping of the vertices back to the super graph vertices.
    *
    * @return The mapping.
    */
    vtx_type const * getSuperMap() const;


    /**
     * @brief Map a sub partitioning of this graph to some other super
     * partitioning.
     *
     * @param subPartitioning The partitioning of this graph.
     * @param superPartitioning The partitioning of the super graph (output).
     */
    void mapPartitioning(
        Partitioning const * subPartitioning,
        Partitioning * superPartitioning) const;


    /**
     * @brief Get the vertex index in the super graph of a vertex in this
     * subgraph.
     *
     * @param vertex The vertex this subgraph.
     *
     * @return The vertex id in the super graph.
     */
    vtx_type getSuperMap(
        vtx_type const vertex) const noexcept
    {
      return m_superMap[vertex];
    }


  private:
    Array<vtx_type> m_superMap;
    ConstantGraph m_graph;
};


}

#endif
