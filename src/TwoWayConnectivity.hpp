/**
* @file TwoWayConnectivity.hpp
* @brief The TwoWayConnectivity class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-19
*/




#ifndef DOLOS_SRC_TWOWAYCONNECTIVITY_HPP
#define DOLOS_SRC_TWOWAYCONNECTIVITY_HPP


#include "FixedSet.hpp"


namespace dolos
{


class TwoWayConnectivity
{
  public:
    struct vertex_struct
    {
      wgt_type external;
      wgt_type internal;
    };


    void move(
        vtx_type const vertex);

    
     


  private:
    FixedSet<vtx_type> m_border[NUM_BISECTION_PARTS];
    Array<vertex_struct> m_connectivity;
};

}

#endif
