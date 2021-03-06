/**
* @file GridGraphGenerator.hpp
* @brief The GridGraphGenerator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-09
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



#ifndef POROS_SRC_GRIDGRAPHGENERATOR_HPP
#define POROS_SRC_GRIDGRAPHGENERATOR_HPP


#include <memory>
#include "Base.hpp"
#include "graph/Graph.hpp"


namespace poros
{

class GridGraphGenerator
{
  public:
    /**
    * @brief Generate a 3D grid graph.
    *
    * @param numX The number of vertices in X.
    * @param numY The number of vertices in Y.
    * @param numZ The number of vertices in Z.
    */
    GridGraphGenerator(
        vtx_type numX,
        vtx_type numY,
        vtx_type numZ);


    /**
    * @brief Default destructor -- required for incomplete type of Grid.
    */
    ~GridGraphGenerator();


    /**
    * @brief Set the random parameters of the vertex weights.
    *
    * @param min The minimum vertex weight (must be greater than 0).
    * @param max The maximum vertex weight.
    */
    void setRandomVertexWeight(
        wgt_type min,
        wgt_type max);


    /**
    * @brief Set the random parameters of the edge weights.
    *
    * @param min The minimum edge weight.
    * @param max The maximum edge weight.
    */
    void setRandomEdgeWeight(
        wgt_type min,
        wgt_type max);


    /**
    * @brief Generate the graph.
    *
    * @return The generated graph.
    */
    Graph generate();

  private:
    // forward declaration
    class Grid;
    
    std::unique_ptr<Grid> m_grid;

    wgt_type m_vertexWeightMin;
    wgt_type m_vertexWeightMax;
    wgt_type m_edgeWeightMin;
    wgt_type m_edgeWeightMax;

};


}



#endif
