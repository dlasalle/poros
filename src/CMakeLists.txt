include_directories(.)

# libraries
add_library(poros ${POROS_LIBRARY_TYPE}
  ${sources}
)

# pull in all sub directory sources
add_subdirectory("util")
add_subdirectory("graph")
add_subdirectory("partition")
add_subdirectory("aggregation")
add_subdirectory("multilevel")

file(GLOB sources *.cpp)
target_sources(poros PRIVATE ${sources})

install(TARGETS poros
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if (DEFINED TESTS AND NOT TESTS EQUAL 0)
  add_subdirectory("test")
endif()



