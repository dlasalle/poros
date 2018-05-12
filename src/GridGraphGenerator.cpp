/**
* @file GridGraphGenerator.cpp
* @brief Implementation of the GridGraphGenerator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-10
*/


#include "GridGraphGenerator.hpp"


#include <vector>
#include "GraphData.hpp"
#include "solidutils/Random.hpp"
#include "solidutils/Debug.hpp"


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
  // do nothing
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


void GridGraphGenerator::setRandomEdgeWeight(
    wgt_type const min,
    wgt_type const max)
{
  m_edgeWeightMin = min;
  m_edgeWeightMax = max;
}


ConstantGraph GridGraphGenerator::generate()
{
  vtx_type const numVertices = m_grid->getNumVertices();
  adj_type const numEdges = m_grid->getNumEdges(); 

  GraphData data(numVertices, numEdges);

  adj_type * const edgePrefix = data.edgePrefix();
  vtx_type * const edgeList = data.edgeList();
  wgt_type * const vertexWeight = data.vertexWeight();
  wgt_type * const edgeWeight = data.edgeWeight();

  vtx_type const numX = m_grid->getNumVerticesX();
  vtx_type const numY = m_grid->getNumVerticesY();
  vtx_type const numZ = m_grid->getNumVerticesZ();

  // each vertex can be the root of up to 3 edges
  std::vector<wgt_type> srcEdgeWeights(numVertices*3);
  sl::Random::fillWithRange(srcEdgeWeights.data(), \
      srcEdgeWeights.size(), m_edgeWeightMin, m_edgeWeightMax);
  
  adj_type edge = 0;
  vtx_type vertex = 0;
  edgePrefix[0] = 0;
  for (vtx_type z = 0; z < numZ; ++z) {
    for (vtx_type y = 0; y < numY; ++y) {
      for (vtx_type x = 0; x < numX; ++x) {
        vtx_type const source = m_grid->get(x, y, z);
        if (x > 0) {
          // place an edge facing back
          vtx_type const dest = m_grid->get(x-1, y, z);
          edgeList[edge] = dest;
          edgeWeight[edge] = srcEdgeWeights[dest*3];
          ++edge;
        }
        if (x < numX-1) {
          // place an edge facing forward 
          vtx_type const dest = m_grid->get(x+1, y, z);
          edgeList[edge] = dest;
          edgeWeight[edge] = srcEdgeWeights[source*3];
          ++edge;
        }

        if (y > 0) {
          // place an edge facing back
          vtx_type const dest = m_grid->get(x, y-1, z);
          edgeList[edge] = dest;
          edgeWeight[edge] = srcEdgeWeights[(dest*3) + 1];
          ++edge;
        }
        if (y < numY-1) {
          // place an edge facing forward 
          vtx_type const dest = m_grid->get(x, y+1, z);
          edgeList[edge] = dest;
          edgeWeight[edge] = srcEdgeWeights[(source*3) + 1];
          ++edge;
        }

        if (z > 0) {
          // place an edge facing back
          vtx_type const dest = m_grid->get(x, y, z-1);
          edgeList[edge] = dest;
          edgeWeight[edge] = srcEdgeWeights[(dest*3) + 2];
          ++edge;
        }
        if (z < numZ-1) {
          // place an edge facing forward 
          vtx_type const dest = m_grid->get(x, y, z+1);
          edgeList[edge] = dest;
          edgeWeight[edge] = srcEdgeWeights[(source*3) + 2];
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
  sl::Random::fillWithRange(vertexWeight, numVertices, \
      m_vertexWeightMin, m_vertexWeightMax);

  return data.toGraph();
}


}
