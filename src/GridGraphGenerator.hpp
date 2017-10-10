/**
* @file GridGraphGenerator.hpp
* @brief The GridGraphGenerator class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-09
*/



namespace dolos
{

class GridGraphGenerator
{
  public:
    /**
    * @brief Generate a 3D grid graph.
    *
    * @param numX The number of vertices in X.
    * @param numY The number of vertices in Y.
    * @param numZ The number of vertices in Z.
    */
    GridGraphGenerator(
        vtx_type numX,
        vtx_type numY,
        vtx_type numZ);


    /**
    * @brief Set the random parameters of the vertex weights.
    *
    * @param min The minimum vertex weight (must be greater than 0).
    * @param max The maximum vertex weight.
    */
    void setRandomVertexWeight(
        wgt_type min,
        wgt_type max);


    /**
    * @brief Generate the graph.
    *
    * @return The generated graph.
    */
    ConstantGraph && generate();

};


}
