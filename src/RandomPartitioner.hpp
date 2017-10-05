/**
 * @file RandomPartitioner.hpp
 * @brief A class for creating a random partition.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-04
 */



namespace dolos
{

class RandomPartitioner :
  public IPartitioner
{
  public:
    /**
     * @brief Create a new random partitioner with the given parameters.
     *
     * @param params The parameters.
     */
    RandomPartitioner(
        Parameters const * params);

    /**
     * @brief Destructor.
     */
    virtual ~RandomPartitioner();

    /**
     * @brief Randomly assign vertices to partitions.
     *
     * @param graph The graph.
     *
     * @return The assigned partitioning.
     */
    virtual Partitioning execute(
        Graph const * graph) const override;

  private:
    pid_type m_numParts;
    std::vector<double> m_targetPartitionFractions;
};


}
