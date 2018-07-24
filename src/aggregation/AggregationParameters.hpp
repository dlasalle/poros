/**
* @file AggregationParameters.hpp
* @brief The AggregationParameters class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-23
*/



#ifndef DOLOS_SRC_AGGREGATIONPARAMETERS_HPP
#define DOLOS_SRC_AGGREGATIONPARAMETERS_HPP

#include "Base.hpp"

namespace dolos
{

class AggregationParameters
{
  public:
    /**
    * @brief Create a new set of aggregation parameters.
    */
    AggregationParameters();

    /**
    * @brief Set the maximum weight of a vertex allowed.
    *
    * @param max The maximum weight.
    */
    void setMaxVertexWeight(
        wgt_type max);

    /**
    * @brief Check if a vertex weight would be acceptable.
    *
    * @param wgt The weight of the proposed vertex.
    *
    * @return True if the weight is within allowed limits.
    */
    inline bool isAllowedVertexWeight(
        wgt_type wgt) const
    {
      // if m_maxVertexWeight has not been set, everything is allowed.
      return wgt == NULL_WGT || wgt <= m_maxVertexWeight;
    }

  private:
  wgt_type m_maxVertexWeight;

};

}

#endif
