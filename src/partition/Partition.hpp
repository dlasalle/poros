/**
* @file Partition.hpp
* @brief The Partition class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-11-03
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


#ifndef POROS_SRC_PARTITION_HPP
#define POROS_SRC_PARTITION_HPP


#include "Base.hpp"


namespace poros
{


class Partition
{
  public:
    /**
    * @brief Create a new partition.
    *
    * @param index The index of the partition.
    * @param partitionWeight The vector of partition weights.
    */
    Partition(
        pid_type const index,
        wgt_type const weight) noexcept :
      m_index(index),
      m_weight(weight)
    {
      // do nothing
    }


    /**
    * @brief Get the index of this partition (it's ID).
    *
    * @return The index.
    */
    inline pid_type index() const noexcept
    {
      return m_index;
    }


    /**
    * @brief Get weight of the partition.
    *
    * @return The weight.
    */
    inline wgt_type weight() const noexcept
    {
      return m_weight;
    }

    private:
      adj_type m_index;
      wgt_type m_weight;
};


}


#endif
