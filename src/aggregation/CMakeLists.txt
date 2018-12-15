file(GLOB sources *.cpp)
target_sources(merizo PRIVATE ${sources})

include_directories(.)

if (DEFINED TESTS AND NOT TESTS EQUAL 0)
  add_subdirectory("test")
endif()


