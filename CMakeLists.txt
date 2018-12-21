cmake_minimum_required(VERSION 2.8)
project(POROS)

if (DEFINED DEBUG)
  add_definitions(-DDEBUG=${DEBUG})
  if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
  endif()
  set(CMAKE_BUILD_TYPE Debug)
  message("Building a debug release")
else()
  set(CMAKE_BUILD_TYPE Release)
  add_definitions(-DNDEBUG=1)
  message("Building an optimized release")
endif()

if (STATIC)
  set(POROS_LIBRARY_TYPE STATIC)
else()
  set(POROS_LIBRARY_TYPE SHARED)
endif()

if (DEFINED DEVEL AND NOT DEVEL EQUAL 0)
  message("Development warnings enabled")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-declarations") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-aliasing") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic") 
endif()


if (DEFINED POROS_DIMENSION_TYPE)
  add_definitions(-DPOROS_DIMENSION_TYPE=${POROS_DIMENSION_TYPE})
endif()

if (DEFINED POROS_INDEX_TYPE)
  add_definitions(-DPOROS_INDEX_TYPE=${POROS_INDEX_TYPE})
endif()

if (DEFINED POROS_VALUE_TYPE)
  add_definitions(-DPOROS_VALUE_TYPE=${POROS_VALUE_TYPE})
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14") 

# use gnu directories
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  include(GNUInstallDirs)
elseif(NOT DEFINED CMAKE_INSTALL_LIBDIR)
  set(CMAKE_INSTALL_LIBDIR "lib") 
endif()

# must be before including src
if (DEFINED TESTS AND NOT TESTS EQUAL 0)
  enable_testing()
endif()

include_directories("include")
include_directories("solidutils")
add_subdirectory("include")
add_subdirectory("src")


if (DEFINED EXAMPLES)
  add_subdirectory("examples")
endif()

