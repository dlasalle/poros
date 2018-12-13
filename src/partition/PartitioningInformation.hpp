/**
* @file PartitioningInformation.hpp
* @brief The PartitioningInformation class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-12-09
*/



#ifndef DOLOS_SRC_PARTITIONINGINFORMATION_HPP
#define DOLOS_SRC_PARTITIONINGINFORMATION_HPP

#include "Partitioning.hpp"
#include "TwoWayConnectivity.hpp"


namespace dolos
{


class PartitioningInformation
{
  public:
    PartitioningInformation(
        Partitioning partitioning,
        TwoWayConnectivity connectivity) :
      m_partitioning(std::move(partitioning)),
      m_connectivity(std::move(connectivity))
    {
    }


    Partitioning * partitioning()
    {
      return &m_partitioning;
    }

    TwoWayConnectivity * connectivity()
    {
      return &m_connectivity;
    }

    Partitioning const * partitioning() const
    {
      return &m_partitioning;
    }

    TwoWayConnectivity const * connectivity() const
    {
      return &m_connectivity;
    }



  private:
    Partitioning m_partitioning;
    TwoWayConnectivity m_connectivity;
};


}

#endif
