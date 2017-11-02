/**
* @file RandomTraverser.hpp
* @brief The RandomTraverser class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-10-06
*/




#ifndef DOLOS_SRC_RANDOMTRAVERSER_HPP
#define DOLOS_SRC_RANDOMTRAVERSER_HPP


#include <vector>
#include <cstdlib>
#include <algorithm>
#include "solidutils/Debug.hpp"


namespace dolos
{


class RandomTraverser
{
  public:
    /**
    * @brief Create a new RandomTraverser.
    *
    * @param size The number of indexes to randomly traverse.
    */
    RandomTraverser(
        size_t const size) :
      m_step(-1),
      m_perm(size)
    {
      fill(&m_perm);
      std::random_shuffle(m_perm.begin(), m_perm.end());
    }

    /**
    * @brief Move to the next index.
    *
    * @return True if the next index is valid, and false if the the end
    * of the array was hit.
    */
    inline bool next()
    {
      ++m_step; 

      return m_step < m_perm.size();
    }

    /**
    * @brief Get the current index.
    *
    * @return The current index in the traversal.
    */
    inline size_t get() const
    {
      ASSERT_LESS(m_step, m_perm.size());

      return m_perm[m_step];
    }

  private:
    static void fill(
        std::vector<size_t> * const perm)
    {
      size_t const size = perm->size();

      for (size_t i = 0; i < size; ++i) {
        (*perm)[i] = i;
      }
    }
      
    size_t m_step;
    std::vector<size_t> m_perm;
};


}


#endif
