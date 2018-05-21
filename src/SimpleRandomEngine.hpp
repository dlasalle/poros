/**
* @file SimpleRandomEngine.hpp
* @brief The SimpleRandomEngine class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-05-20
*/


#ifndef DOLOS_SRC_SIMPLERANDOMENGINE_HPP
#define DOLOS_SRC_SIMPLERANDOMENGINE_HPP


#include "IRandomEngine.hpp"
#include <random>

namespace dolos
{


class SimpleRandomEngine : public IRandomEngine
{
  public:
  SimpleRandomEngine(
      unsigned int seed = 0);


  private:
  std::mt19937 m_rng;
};

}

#endif


