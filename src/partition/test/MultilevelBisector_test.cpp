/**
* @file MultilevelBisector_test.cpp
* @brief Unit tests for the MultilevelBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-16
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


#include "partition/MultilevelBisector.hpp"
#include "aggregation/RandomMatchingAggregator.hpp"
#include "partition/BFSBisector.hpp"
#include "partition/PartitioningAnalyzer.hpp"
#include "partition/FMRefiner.hpp"
#include "graph/GridGraphGenerator.hpp"
#include "util/RandomEngineFactory.hpp"
#include "util/TimeKeeper.hpp"

#include "solidutils/UnitTest.hpp"

namespace poros
{


UNITTEST(MultilevelBisector, ExecuteFullCoarsen8Part)
{
  // build a grid graph
  GridGraphGenerator gen(40, 40, 1);

  Graph graph = gen.generate();

  // builder our ml bisector
  RandomEngineHandle engine = RandomEngineFactory::make(0);

  std::unique_ptr<IAggregator> agg(new RandomMatchingAggregator(engine));
  std::unique_ptr<IBisector> bis(new BFSBisector(engine));
  std::unique_ptr<ITwoWayRefiner> ref(new FMRefiner(8, 20));

  std::shared_ptr<TimeKeeper> timeKeeper(new TimeKeeper);
  MultilevelBisector mb(std::move(agg), std::move(bis), std::move(ref), timeKeeper);

  // set target partitioning
  TargetPartitioning target(2, graph.getTotalVertexWeight(), 0.005);

  Partitioning part = mb.execute(&target, &graph);

  wgt_type const maxCut = 80;
  wgt_type const minCut = 40;

  PartitioningAnalyzer analyzer(&part, &target);

  testLessOrEqual(part.getCutEdgeWeight(), maxCut);
  testGreaterOrEqual(part.getCutEdgeWeight(), minCut);

  // balanced to within 0.51%
  testLess(analyzer.calcMaxImbalance(), 0.0051);
}

}
