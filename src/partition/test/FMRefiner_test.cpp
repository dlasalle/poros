/**
* @file FMRefiner_test.cpp
* @brief Unit test for the FMRefiner class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018
* @version 1
* @date 2017-11-05
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



#include "partition/FMRefiner.hpp"
#include "partition/RandomBisector.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "solidutils/UnitTest.hpp"

namespace poros
{

UNITTEST(FMRefiner, RefineRandomGridCut)
{
  // graph with 210 vertices and a minimum bisection of 30 
  GridGraphGenerator gen(5, 6, 7); 

  Graph graph = gen.generate();

  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.03);

  FMRefiner fm(25, graph.numVertices());

  RandomEngineHandle engine = RandomEngineFactory::make(0);

  RandomBisector bisector(engine);

  Partitioning part = bisector.execute(&target, &graph); 

  TwoWayConnectivity conn = \
      TwoWayConnectivity::fromPartitioning(&graph, &part);

  fm.refine(&target, &conn, &part, &graph);

  testLess(part.getCutEdgeWeight(), 100u);

  PartitioningAnalyzer analyzer(&part, &target);

  testLess(analyzer.calcMaxImbalance(), 0.03005);
}

UNITTEST(FMRefiner, RefineUnbalancedCut)
{
  // graph with 210 vertices and a minimum bisection of 30 
  GridGraphGenerator gen(5, 6, 7); 

  Graph graph = gen.generate();

  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.03);
  Partitioning part(2, &graph);
  part.assignAll(0);
  part.move(Vertex::make(0), 1);
  part.move(Vertex::make(1), 1);
  part.move(Vertex::make(2), 1);
  part.move(Vertex::make(3), 1);
  part.move(Vertex::make(4), 1);
  part.recalcCutEdgeWeight();

  FMRefiner fm(25, graph.numVertices());

  TwoWayConnectivity conn = \
      TwoWayConnectivity::fromPartitioning(&graph, &part);

  fm.refine(&target, &conn, &part, &graph);

  testLessOrEqual(part.getCutEdgeWeight(), 60u);

  PartitioningAnalyzer analyzer(&part, &target);

  testLess(analyzer.calcMaxImbalance(), 0.03005);
}

}
