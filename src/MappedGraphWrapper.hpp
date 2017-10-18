/**
 * @fileMappedGraphWrapper.hpp
 * @brief TheMappedGraphWrapper class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-17
 */


#ifndef DOLOS_SRC_MAPPEDGRAPH_HPP
#define DOLOS_SRC_MAPPEDGRAPH_HPP


#include "IMappedGraph.hpp"


namespace dolos
{

classMappedGraphWrapper :
    public IMappedGraph
{
  public:
    /**
     * @brief Create a new mapped graph where each vertex is mapped to itself.
     *
     * @param graph The graph to map.
     */
   MappedGraphWrapper(
        ConstantGraph const * graph); 


    /**
     * @brief Get the underyling graph.
     *
     * @return The graph.
     */
    virtual ConstantGraph const * getGraph() const override;


    /**
     * @brief Map a sub partitioning of this graph to some other super
     * partitioning.
     *
     * @param subPartitioning The partitioning of this graph.
     * @param superPartitioning The partitioning of the super graph (output).
     * @param offset The offset of partition IDs in the subgraph compared to
     * the super graph.
     */
    virtual void mapPartitioning(
        Partitioning const * subPartitioning,
        Partitioning * superPartitioning,
        pid_type offset) const override;


  private:
    ConstantGraph const * const m_graph; 

    // disable copying
   MappedGraphWrapper(
       MappedGraphWrapper const & rhs); 
   MappedGraphWrapper & operator=(
       MappedGraphWrapper const & rhs); 
};

}

#endif
