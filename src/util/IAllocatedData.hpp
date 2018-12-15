/**
* @file IAllocatedData.hpp
* @brief The IAllocatedData interface.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-10
*/




#ifndef POROS_SRC_IALLOCATEDDATA_HPP
#define POROS_SRC_IALLOCATEDDATA_HPP


namespace poros
{


/**
* @brief The purpose of this interface is to provide a means of tying two
* objects destruction together.
*/
class IAllocatedData
{
  public:
    /**
    * @brief Destructor to be overridden.
    */
    virtual ~IAllocatedData()
    {
      // do nothing
    }

};

}

#endif
