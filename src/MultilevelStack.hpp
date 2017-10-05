/**
 * @file MultilevelStack.hpp
 * @brief The MultilevelStack class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */


#include "Graph.hpp"
#include "Partitioning.hpp"


namespace dolos
{


class MultilevelStack
{
  public:
    MultilevelStack(
        Graph const * base);

    Graph const * getTop() const;

    int getLevel() const;

    void coarsen();

    void uncoarsen();
}

}
