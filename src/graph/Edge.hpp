/**
* @file Edge.hpp
* @brief The Edge class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-23
*/



#ifndef POROS_SRC_EDGE_HPP
#define POROS_SRC_EDGE_HPP


#include "Base.hpp"


namespace poros
{

struct Edge
{
  constexpr static Edge make(
      adj_type const vtx) noexcept
  {
    return Edge{vtx};
  }

  adj_type index;

  constexpr bool operator==(
      Edge const lhs) const noexcept
  {
    return index == lhs.index;
  }

  constexpr bool operator!=(
      Edge const lhs) const noexcept 
  {
    return !(*this == lhs);
  }

  constexpr bool operator<(
      Edge const lhs) const noexcept 
  {
    return index < lhs.index;
  }

  constexpr bool operator<=(
      Edge const lhs) const noexcept 
  {
    return index <= lhs.index;
  }

  constexpr operator adj_type() const noexcept 
  {
    return index;
  }
      
};


}

#endif
