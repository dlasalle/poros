/**
* @file RandomOrderVertexSet.cpp
* @brief Implementation of the RandomOrderVertexSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-21
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

#include "RandomOrderVertexSet.hpp"
#include "util/RandomEngine.hpp"

namespace poros
{


/******************************************************************************
* PUBLIC STATIC METHODS *******************************************************
******************************************************************************/

PermutedVertexSet RandomOrderVertexSet::generate(
    VertexSet const set,
    RandomEngine * const randomEngine)
{
  vtx_type const numVertices = set.size();
  std::unique_ptr<vtx_type[]> perm(new vtx_type[numVertices]);

  randomEngine->fillWithPerm(perm.get(), 0, numVertices);

  return PermutedVertexSet(std::move(perm), numVertices);
}


}
