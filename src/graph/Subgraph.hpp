/**
* @file Subgraph.hpp
* @brief The Subgraph class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-10
*/




#ifndef DOLOS_SRC_SUBGRAPH_HPP
#define DOLOS_SRC_SUBGRAPH_HPP


#include "graph/GraphHandle.hpp"
#include "partition/Partitioning.hpp"
#include "graph/IMappedGraph.hpp"
#include "solidutils/Array.hpp"


namespace dolos
{

class Subgraph :
    public IMappedGraph
{
  public:
    /**
    * @brief Create a new subgraph.
    *
    * @param superGraph The super graph.
    * @param superMap The mapping of vertices to the super graph.
    */
    Subgraph(
        GraphHandle superGraph,
        sl::Array<vtx_type> superMap);


    /**
    * @brief Create a new subgraph with a mapping which maps vertices to
    * themselves.
    *
    * @param superGraph The super graph.
    */
    Subgraph(
        GraphHandle superGraph);


    /**
    * @brief Get the underlying graph.
    *
    * @return The graph.
    */
    Graph const * getGraph() const override;


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
     * @param partitionLabels The partition labels of the super graph (output).
     * @param offset The offset of partition IDs in the subgraph compared to
     * the super graph.
     */
    void mapPartitioning(
        Partitioning const * subPartitioning,
        pid_type * partitionLabels,
        pid_type offset) const override;


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
    sl::Array<vtx_type> m_superMap;
    GraphHandle m_graph;
};


}

#endif
