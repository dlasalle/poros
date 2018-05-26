file(GLOB sources *.cpp)
target_sources(dolos PRIVATE ${sources})

if (DEFINED TESTS AND NOT TESTS EQUAL 0)
  add_subdirectory("test")
endif()


