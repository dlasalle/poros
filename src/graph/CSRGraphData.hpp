/**
* @file CSRGraphData.hpp
* @brief The CSRGraphData class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-12
*/



#ifndef DOLOS_SRC_CSRGRAPHDATA_HPP
#define DOLOS_SRC_CSRGRAPHDATA_HPP

#include "Base.hpp"

namespace dolos
{

class CSRGraphData
{
  public:
    /**
    * @brief Create a new CSRGraphData collection.
    *
    * @param edgePrefix The edge prefix.
    * @param edgeList The edge list.
    * @param vertexWeight The vertex weight.
    * @param edgeWeight The edge weight.
    */
    CSRGraphData(
        adj_type const * edgePrefix,
        vtx_type const * edgeList,
        wgt_type const * vertexWeight,
        wgt_type const * edgeWeight) :
      m_edgePrefix(edgePrefix),
      m_edgeList(edgeList),
      m_vertexWeight(vertexWeight),
      m_edgeWeight(edgeWeight)
    {
      // do nothing
    }


    /**
    * @brief Copy constructor.
    *
    * @param rhs The data to copy.
    */
    CSRGraphData(
        CSRGraphData const & rhs) :
      CSRGraphData(
        rhs.m_edgePrefix,
        rhs.m_edgeList,
        rhs.m_vertexWeight,
        rhs.m_edgeWeight)
    {
      // do nothing
    }


    /**
    * @brief Copy assignment operator.
    *
    * @param rhs The data to copy.
    *
    * @return This data.
    */
    CSRGraphData& operator=(
        CSRGraphData const & rhs)
    {
      m_edgePrefix = rhs.m_edgePrefix;
      m_edgeList = rhs.m_edgeList;
      m_vertexWeight = rhs.m_vertexWeight;
      m_edgeWeight = rhs.m_edgeWeight;

      return *this;
    }


    /**
    * @brief Get the pointer to the edge prefix.
    *
    * @return The pointer.
    */
    adj_type const * edgePrefix() const noexcept
    {
      return m_edgePrefix;
    }


    /**
    * @brief Get the pointer to the edge list.
    *
    * @return The pointer.
    */
    vtx_type const * edgeList() const noexcept
    {
      return m_edgeList;
    }


    /**
    * @brief Get the pointer to the vertex weights.
    *
    * @return The pointer.
    */
    wgt_type const * vertexWeight() const noexcept
    {
      return m_vertexWeight;
    }


    /**
    * @brief Get the pointer to the edge weights.
    *
    * @return The pointer.
    */
    wgt_type const * edgeWeight() const noexcept
    {
      return m_edgeWeight;
    }

  private:
    adj_type const * m_edgePrefix;
    vtx_type const * m_edgeList;
    wgt_type const * m_vertexWeight;
    wgt_type const * m_edgeWeight;



};

}

#endif
