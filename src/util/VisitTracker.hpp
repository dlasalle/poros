/**
* @file VisitTracker.hpp
* @brief The VisitTracker class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-24
*/


#ifndef POROS_UTIL_VISITTRACKER_HPP
#define POROS_UTIL_VISITTRACKER_HPP


#include <cstdlib>
#include <vector>


namespace poros
{

/**
* @brief This class is used for tracking visition of indexes. It is just a
* wrapper around std::vector<bool>, but provides the visitation semantics.
*/
class VisitTracker
{
  public:
    /**
    * @brief Create a new visit tracker.
    *
    * @param size The number of indicies in the tracker.
    */
    VisitTracker(
        size_t const size) :
      m_bits(size, false)
    {
      // do nothing
    }

    /**
    * @brief Mark an index as visited.
    *
    * @param index The index to mark.
    */
    void visit(
        size_t const index)
    {
      m_bits[index] = true;
    }

    /**
    * @brief Remove the visited status from an index.
    *
    * @param index The index to un-visit.
    */
    void unvisit(
        size_t const index)
    {
      m_bits[index] = false;
    }

    /**
    * @brief Check if an index has been visited.
    *
    * @param index The visited index.
    *
    * @return True if the index has been visited.
    */
    bool hasVisited(
        size_t const index) const
    {
      return m_bits[index];
    }

    /**
    * @brief Reset all indices to unvisited.
    */
    void clear()
    {
      m_bits.assign(m_bits.size(), false);
    }

    /**
    * @brief Get the number of indicies tracked.
    *
    * @return The number of indices.
    */
    size_t size() const
    {
      return m_bits.size();
    }

  private:
    std::vector<bool> m_bits;
};

}

#endif
