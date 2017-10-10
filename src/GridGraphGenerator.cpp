/**
* @file GridGraphGenerator.cpp
* @brief Implementation of the GridGraphGenerator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/



#include "GridGraphGenerator.hpp"

#include "Random.hpp"
#include "Debug.hpp"
#include "GraphData.hpp"


namespace dolos
{



/******************************************************************************
* PRIVATE CLASSES *************************************************************
******************************************************************************/

class GridGraphGenerator::Grid
{
  public:
    Grid(
        vtx_type const numX,
        vtx_type const numY,
        vtx_type const numZ) :
      m_numX(numX),
      m_numY(numY),
      m_numZ(numZ)
    {
      ASSERT_GREATER(numX, 0);
      ASSERT_GREATER(numY, 0);
      ASSERT_GREATER(numZ, 0);
    }

    inline vtx_type getNumVertices() const noexcept
    {
      return m_numX*m_numY*m_numZ;
    }

    inline adj_type getNumEdges() const noexcept
    {
      return (((m_numX - 1) * (m_numY*m_numZ)) + \
          ((m_numY - 1) * (m_numX*m_numZ)) + \
          ((m_numZ - 1) * (m_numX*m_numY))) * 2;
    }

    inline vtx_type getNumVerticesX() const noexcept
    {
      return m_numX;
    }

    inline vtx_type getNumVerticesY() const noexcept
    {
      return m_numY;
    }

    inline vtx_type getNumVerticesZ() const noexcept
    {
      return m_numZ;
    }

    inline vtx_type get(
        vtx_type const x,
        vtx_type const y,
        vtx_type const z) const noexcept
    {
      ASSERT_LESS(x, m_numX);
      ASSERT_LESS(y, m_numY);
      ASSERT_LESS(z, m_numZ);

      return (((z*m_numY)+y)*m_numX) + x;
    }

  private:
    vtx_type m_numX;
    vtx_type m_numY;
    vtx_type m_numZ;

};


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

GridGraphGenerator::GridGraphGenerator(
    vtx_type const numX,
    vtx_type const numY,
    vtx_type const numZ) :
  m_grid(new Grid(numX, numY, numZ)),
  m_vertexWeightMin(1),
  m_vertexWeightMax(1),
  m_edgeWeightMin(1),
  m_edgeWeightMax(1)
{
}


GridGraphGenerator::~GridGraphGenerator() = default;


/******************************************************************************
* PUBLIC FUNCTIONS ************************************************************
******************************************************************************/

void GridGraphGenerator::setRandomVertexWeight(
    wgt_type const min,
    wgt_type const max)
{
  m_vertexWeightMin = min;
  m_vertexWeightMax = max;
}


ConstantGraph GridGraphGenerator::generate()
{
  vtx_type const numVertices = m_grid->getNumVertices();
  adj_type const numEdges = m_grid->getNumEdges(); 

  GraphData data(numVertices, numEdges);

  adj_type * const edgePrefix = data.getEdgePrefix();
  vtx_type * const edgeList = data.getEdgeList();
  wgt_type * const vertexWeight = data.getVertexWeight();
  wgt_type * const edgeWeight = data.getEdgeWeight();

  vtx_type const numX = m_grid->getNumVerticesX();
  vtx_type const numY = m_grid->getNumVerticesY();
  vtx_type const numZ = m_grid->getNumVerticesZ();
  
  adj_type edge = 0;
  vtx_type vertex = 0;
  edgePrefix[0] = 0;
  for (vtx_type z = 0; z < numZ; ++z) {
    for (vtx_type y = 0; y < numY; ++y) {
      for (vtx_type x = 0; x < numX; ++x) {
        if (x > 0) {
          // place an edge facing back
          edgeList[edge] = m_grid->get(x-1, y, z); 
          edgeWeight[edge] = 1;
          ++edge;
        }
        if (x < numX-1) {
          // place an edge facing forward 
          edgeList[edge] = m_grid->get(x+1, y, z); 
          edgeWeight[edge] = 1;
          ++edge;
        }

        if (y > 0) {
          // place an edge left back
          edgeList[edge] = m_grid->get(x, y-1, z); 
          edgeWeight[edge] = 1;
          ++edge;
        }
        if (y < numY-1) {
          // place an edge right back
          edgeList[edge] = m_grid->get(x, y+1, z); 
          edgeWeight[edge] = 1;
          ++edge;
        }

        if (z > 0) {
          // place an edge down back
          edgeList[edge] = m_grid->get(x, y, z-1); 
          edgeWeight[edge] = 1;
          ++edge;
        }
        if (z < numZ-1) {
          // place an edge up back
          edgeList[edge] = m_grid->get(x, y, z+1); 
          edgeWeight[edge] = 1;
          ++edge;
        }

        edgePrefix[vertex+1] = edge;
        ++vertex;
      }
    }
  }
  ASSERT_EQUAL(vertex, numVertices);
  ASSERT_EQUAL(edge, numEdges);

  // set vertex weights
  Random::fillWithRange(vertexWeight, numVertices, m_vertexWeightMin, \
      m_vertexWeightMax);

  return data.toGraph();
}


}
