/**
* @file Vertex.hpp
* @brief The Vertex class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-23
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
