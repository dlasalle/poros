/**
 * @file Debug.hpp
 * @brief Debugging functions.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017
 * @version 1
 * @date 2017-10-03
 */


#ifndef DOLOS_SRC_DEBUG_HPP
#define DOLOS_SRC_DEBUG_HPP

#include <cassert>
#include <iostream>


/******************************************************************************
* MACROS **********************************************************************
******************************************************************************/


#ifndef NDEBUG
  #define ASSERT_TRUE(a) \
    do { \
      if (!(a)) { \
        std::cerr << "("#a" = " << (a) << ")" << std::endl; \
        assert(false); \
      } \
    } while (false)
  #define ASSERT_FALSE(a) \
    do { \
      if (a) { \
        std::cerr << "("#a" = " << (a) << ")" << std::endl; \
        assert(false); \
      } \
    } while (false)
  #define ASSERT_EQUAL(a,b) \
    do { \
      if (a != b) { \
        std::cerr << "("#a" = " << (a) << ") != ("#b" = " << (b) << ")" << \
            std::endl; \
        assert(false); \
      } \
    } while (false)
  #define ASSERT_NOTEQUAL(a,b) \
    do { \
      if (a == b) { \
        std::cerr << "("#a" = " << (a) << ") == ("#b" = " << (b) << ")" << \
            std::endl; \
        assert(false); \
      } \
    } while (false)
  #define ASSERT_NULL(a) \
    do { \
      if (a != nullptr) { \
        std::cerr << "("#a" = " << (a) << ") != nullptr" << \
            std::endl; \
        assert(false); \
      } \
    } while (false)
  #define ASSERT_NOTNULL(a) \
    do { \
      if (a == nullptr) { \
        std::cerr << #a" is  null" << \
            std::endl; \
        assert(false); \
      } \
    } while (false)
  #define ASSERT_LESS(a,b) \
    do { \
      if (a >= b) { \
        std::cerr << "("#a" = " << (a) << ") !< ("#b" = " << (b) << ")" << \
            std::endl; \
        assert(false); \
      } \
    } while (false)
  #define ASSERT_LESSEQUAL(a,b) \
    do { \
      if (a > b) { \
        std::cerr << "("#a" = " << (a) << ") !<= ("#b" = " << (b) << ")" << \
            std::endl; \
        assert(false); \
      } \
    } while (false)
  #define ASSERT_GREATER(a,b) \
    do { \
      if (a <= b) { \
        std::cerr << "("#a" = " << (a) << ") !> ("#b" = " << (b) << ")" << \
            std::endl; \
        assert(false); \
      } \
    } while (false)
  #define ASSERT_GREATEREQUAL(a,b) \
    do { \
      if (a < b) { \
        std::cerr << "("#a" = " << (a) << ") !>= ("#b" = " << (b) << ")" << \
            std::endl; \
        assert(false); \
      } \
    } while (false)

#else
  #define ASSERT_TRUE(a)
  #define ASSERT_FALSE(a)
  #define ASSERT_EQUAL(a,b)
  #define ASSERT_NOTEQUAL(a,b)
  #define ASSERT_NULL(a)
  #define ASSERT_NOTNULL(a)
  #define ASSERT_LESS(a,b)
  #define ASSERT_LESSEQUAL(a,b)
  #define ASSERT_GREATER(a,b)
  #define ASSERT_GREATEREQUAL(a,b)
#endif

#endif
