/**
* @file RecursiveBisectionPartitioner.hpp
* @brief The RecursiveBisectionPartitioner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-10-06
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



#ifndef POROS_SRC_RECURSIVEBISECTIONPARTITIONER_HPP
#define POROS_SRC_RECURSIVEBISECTIONPARTITIONER_HPP


#include "partition/IPartitioner.hpp"
#include "partition/IBisector.hpp"
#include "graph/IMappedGraph.hpp"


namespace poros
{


class RecursiveBisectionPartitioner :
  public IPartitioner
{
  public:
    /**
    * @brief Create a new recursive bisection partitioner given the parameters.
    *
    * @param params The parameters to use when partitioning.
    * @param bisector The bisector to use.
    */
    RecursiveBisectionPartitioner(
        IBisector * bisector);


    /**
     * @brief Create a partitioning of the graph.
     *
     * @param target The target partitioning to achieve.
     * @param graph The graph to partition.
     *
     * @return The partitioning.
     */
    Partitioning execute(
        TargetPartitioning const * target,
        Graph const * graph) override;


  private:
    IBisector * m_bisector;


    /**
     * @brief Recursively execute on a subgraph.
     *
     * @param partitionLabels The partitioning to populate.
     * @param target The target partitioning to achieve.
     * @param subGraph The subgraph to recursively partition.
     * @param offset The partition ID offset to assign.
     */
    void recurse(
        pid_type * partitionLabels,
        TargetPartitioning const * target,
        IMappedGraph const * subGraph,
        pid_type const offset);


    // disable copying
    RecursiveBisectionPartitioner(
        RecursiveBisectionPartitioner const & lhs);
    RecursiveBisectionPartitioner & operator=(
        RecursiveBisectionPartitioner const & lhs);

};


}


#endif
