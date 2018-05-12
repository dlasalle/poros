/**
* @file ICSRGraphData.hpp
* @brief The ICSRGraphData interface.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-12
*/



#ifndef DOLOS_SRC_ICSRGRAPHDATA_HPP
#define DOLOS_SRC_ICSRGRAPHDATA_HPP

#include "Base.hpp"

namespace dolos
{

class ICSRGraphData
{
  public:
    /**
    * @brief Virtual destructor.
    */
    virtual ~ICSRGraphData()
    {
      // do nothing
    }

    /**
    * @brief Get the pointer to the edge prefix.
    *
    * @return The pointer.
    */
    virtual adj_type const * edgePrefix() const noexcept = 0;


    /**
    * @brief Get the pointer to the edge list.
    *
    * @return The pointer.
    */
    virtual vtx_type const * edgeList() const noexcept = 0;


    /**
    * @brief Get the pointer to the vertex weights.
    *
    * @return The pointer.
    */
    virtual wgt_type const * vertexWeight() const noexcept = 0;


    /**
    * @brief Get the pointer to the edge weights.
    *
    * @return The pointer.
    */
    virtual wgt_type const * edgeWeight() const noexcept = 0;


};

}

#endif
