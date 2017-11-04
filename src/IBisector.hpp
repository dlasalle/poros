/**
 * @file IBisector.hpp
 * @brief The Bisector interface.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */

#ifndef DOLOS_SRC_IBISECTOR_HPP
#define DOLOS_SRC_IBISECTOR_HPP


#include "IPartitioner.hpp"


namespace dolos
{

class IBisector :
    public IPartitioner
{
  public:
    /**
    * @brief Virtual destructor to prevent memory leaks.
    */
    virtual ~IBisector() 
    {
      // do nothing
    }


};


}


#endif
