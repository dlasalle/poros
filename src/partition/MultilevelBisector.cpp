/**
* @file MultilevelBisector.cpp
* @brief Implementation of the MultilevelBisector class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-07-09
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
#include "multilevel/DiscreteCoarseGraph.hpp"
#include "partition/TwoWayConnectivity.hpp"
#include "multilevel/CompositeStoppingCriteria.hpp"
#include "multilevel/EdgeRatioStoppingCriteria.hpp"
#include "multilevel/VertexNumberStoppingCriteria.hpp"

#include "solidutils/Timer.hpp"

#include <iostream>

namespace poros
{


/******************************************************************************
* CONSTRUCTORS / DESTRUCTOR ***************************************************
******************************************************************************/

MultilevelBisector::MultilevelBisector(
    std::unique_ptr<IAggregator> aggregator,
    std::unique_ptr<IBisector> initialBisector,
    std::unique_ptr<ITwoWayRefiner> refiner,
    std::shared_ptr<TimeKeeper> timeKeeper) :
  m_aggregator(std::move(aggregator)),
  m_initialBisector(std::move(initialBisector)),
  m_refiner(std::move(refiner)),
  m_timeKeeper(timeKeeper)
{
  // do nothing
}



/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

Partitioning MultilevelBisector::execute(
    TargetPartitioning const * target,
    Graph const * graph)
{
  CompositeStoppingCriteria criteria;

  AggregationParameters params;

  // we know we'll have two partitions -- keep 10 in each
  vtx_type const targetNumVertices = 20;

  criteria.add(std::unique_ptr<IStoppingCriteria>(
      new VertexNumberStoppingCriteria(targetNumVertices)));
  criteria.add(std::unique_ptr<IStoppingCriteria>(
      new EdgeRatioStoppingCriteria(0.95)));

  params.setMaxVertexWeight(static_cast<wgt_type>( \
      (1.5 * graph->getTotalVertexWeight()) / targetNumVertices));

  PartitioningInformation partInfo = \
      recurse(0, params, &criteria, target, nullptr, graph);

  return std::move(*(partInfo.partitioning()));
}


/******************************************************************************
* PROTECTED METHODS ***********************************************************
******************************************************************************/

PartitioningInformation MultilevelBisector::recurse(
    int const level,
    AggregationParameters const params,
    IStoppingCriteria const * const stoppingCriteria,
    TargetPartitioning const * const target,
    Graph const * const parent,
    Graph const * const graph)
{
   std::cout << "Coarsened graph to " +
      std::to_string(graph->numVertices()) +
      " vertices and " + std::to_string(graph->numEdges()) +
      " edges, with an exposed weight of " +
      std::to_string(graph->getTotalEdgeWeight()) + "." << std::endl;

  if (stoppingCriteria->shouldStop(level, parent, graph)) {
    Partitioning part = m_initialBisector->execute(target, graph); 
    TwoWayConnectivity conn = \
        TwoWayConnectivity::fromPartitioning(graph, &part);
    return PartitioningInformation(std::move(part), std::move(conn));
  } else {
    sl::Timer coarsenTmr;
    coarsenTmr.start();
    Aggregation agg = m_aggregator->aggregate(params, graph);

    sl::Timer contractTmr;
    contractTmr.start();
    DiscreteCoarseGraph coarse(graph, &agg);
    contractTmr.stop();
    std::cout << "Contraction took: " << contractTmr.poll() << std::endl;
    m_timeKeeper->reportTime(TimeKeeper::CONTRACTION, contractTmr.poll());

    coarsenTmr.stop();
    m_timeKeeper->reportTime(TimeKeeper::COARSENING, coarsenTmr.poll());

    // recurse
    PartitioningInformation coarsePartInfo = recurse( \
        level+1, params, stoppingCriteria, target, graph, coarse.graph());

    sl::Timer uncoarsenTmr;
    uncoarsenTmr.start();

    sl::Timer projectTmr;
    projectTmr.start();
    PartitioningInformation finePartInfo = coarse.project(&coarsePartInfo); 
    projectTmr.stop();
    m_timeKeeper->reportTime(TimeKeeper::PROJECTION, projectTmr.poll());

    m_refiner->refine(target, finePartInfo.connectivity(),
        finePartInfo.partitioning(), graph);
    uncoarsenTmr.stop();
    m_timeKeeper->reportTime(TimeKeeper::UNCOARSENING, uncoarsenTmr.poll());

    return finePartInfo;
  }
}




}
