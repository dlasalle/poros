/**
* @file VertexGroup.hpp
* @brief The VertexGroup class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-12
*/



#ifndef DOLOS_SRC_VERTEXGROUP_HPP
#define DOLOS_SRC_VERTEXGROUP_HPP

#include "graph/PermutedVertexSet.hpp"

namespace dolos
{

class VertexGroup
{
  public:
    /**
    * @brief Create a new vertex group.
    *
    * @param size The size of the group.
    * @param fineVertices The set of fine vertices in the group.
    * @param data The graph data.
    */
    VertexGroup(
        vtx_type const size,
        vtx_type const * const fineVertices) noexcept :
      m_size(size),
      m_fineVertices(fineVertices)
    {
      // do nothing 
    }

    /**
    * @brief Get the fine vertices that make up this vertex group.
    *
    * @return The set of fine vertices.
    */
    PermutedVertexSet fineVertices() const noexcept
    {
      // TODO: make VertexSet a templated class taking in an iterator
      return PermutedVertexSet(m_fineVertices, m_size); 
    }

    /**
    * @brief Get the number of vertices in this group.
    *
    * @return The number of vertices.
    */
    vtx_type size() const
    {
      return m_size;
    }

  private:
    vtx_type const m_size;
    vtx_type const * const m_fineVertices;
    
};

}

#endif
