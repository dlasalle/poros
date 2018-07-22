/**
 * @file VertexNumberStoppingCriteria.hpp
 * @brief The VertexNumberStoppingCriteria class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-07-22
 */


#ifndef DOLOS_SRC_VERTEXNUMBERSTOPPINGCRITERIA_HPP
#define DOLOS_SRC_VERTEXNUMBERSTOPPINGCRITERIA_HPP

#include "multilevel/IStoppingCriteria.hpp"

namespace dolos
{


class VertexNumberStoppingCriteria : public IStoppingCriteria 
{
  public:
    /**
     * @brief Create a new VertexNumberStoppingCriteria object.
     *
     * @param numVertices The number of vertices at which to stop.
     */
    VertexNumberStoppingCriteria(
        vtx_type numVertices);

    /**
     * @brief Determine if coarsening should terminate based on the number of
     * vertices in the coarse graph.
     *
     * @param level The level of the coarsest graph.
     * @param fine The fine graph (previous -- may be nullptr).
     * @param coarse The coarse graph (next).
     *
     * @return True if coarseing should stop at the coarse graph.
     */
    bool shouldStop(
        int level,
        ConstantGraph const * fine,
        ConstantGraph const * coarse) const override;

  private:
    vtx_type m_numVertices;
};


}

#endif

