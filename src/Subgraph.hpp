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


  private:
    Array<vtx_type> m_superMap;
    ConstantGraph m_graph;
};


}

#endif
