/**
* @file Vertex.hpp
* @brief The Vertex class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-23
*/


#ifndef POROS_SRC_VERTEX_HPP
#define POROS_SRC_VERTEX_HPP

#include "Base.hpp"

namespace poros
{

struct Vertex
{
  constexpr static Vertex make(
      vtx_type const vtx) noexcept
  {
    return Vertex{vtx};
  }

  vtx_type index;

  constexpr bool operator==(
      Vertex const lhs) const noexcept
  {
    return index == lhs.index;
  }

  constexpr bool operator!=(
      Vertex const lhs) const noexcept
  {
    return !(*this == lhs);
  }

  constexpr bool operator<(
      Vertex const lhs) const noexcept
  {
    return index < lhs.index;
  }

  constexpr bool operator<=(
      Vertex const lhs) const noexcept
  {
    return index <= lhs.index;
  }

  constexpr operator vtx_type() const noexcept 
  {
    return index;
  }
 
};

}


#endif
