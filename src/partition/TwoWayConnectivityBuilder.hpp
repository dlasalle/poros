/**
* @file TwoWayConnectivityBuilder.hpp
* @brief The TwoWayConnectivity class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-12-11
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



#ifndef POROS_SRC_TWOWAYCONNECTIVITYBUILDER_HPP
#define POROS_SRC_TWOWAYCONNECTIVITYBUILDER_HPP

#include "partition/TwoWayConnectivity.hpp"

namespace poros
{


class TwoWayConnectivityBuilder
{
  public:
    using vertex_struct = TwoWayConnectivity::vertex_struct;

    /**
    * @brief Create a new TwoWayConnectivity object.
    */
    TwoWayConnectivityBuilder();

    /**
    * @brief Begin building a connectivity with the given number of vertices.
    *
    * @param numVertices The number of vertices in the new connectivity object.
    */
    void begin(
        vtx_type numVertices);

    /**
    * @brief Set the internal connectivity of the given vertex.
    *
    * @param vertex The vertex.
    * @param weight The weight of edges connecting to this partition.
    */
    void setInternalConnectivityOf(
        Vertex const vertex,
        wgt_type const weight) noexcept
    {
      ASSERT_LESS(static_cast<size_t>(vertex.index), m_connectivity.size());
      m_connectivity[vertex.index].internal = weight;
    }

    /**
    * @brief Set the external connectivity of the given vertex.
    *
    * @param vertex The vertex.
    * @param weight The weight of edges connecting to the other partition.
    */
    void setExternalConnectivityOf(
        Vertex const vertex,
        wgt_type const weight) noexcept
    {
      ASSERT_LESS(static_cast<size_t>(vertex.index), m_connectivity.size());
      m_connectivity[vertex.index].external = weight;
    }

    /**
    * @brief Finish building this TwoWayConnectivity.
    *
    * @return The build object.
    */
    TwoWayConnectivity finish();

  private:
    sl::Array<vertex_struct> m_connectivity;
};

}


#endif

