/**
* @file VertexGroup.hpp
* @brief The VertexGroup class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-12
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/



#ifndef POROS_SRC_VERTEXGROUP_HPP
#define POROS_SRC_VERTEXGROUP_HPP

#include "graph/PermutedVertexSet.hpp"

namespace poros
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
