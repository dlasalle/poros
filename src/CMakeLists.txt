include_directories(.)

# libraries
add_library(merizo ${POROS_LIBRARY_TYPE} 
  ${sources}
) 

# pull in all sub directory sources
add_subdirectory("util")
add_subdirectory("graph")
add_subdirectory("partition")
add_subdirectory("aggregation")
add_subdirectory("multilevel")

file(GLOB sources *.cpp)
target_sources(merizo PRIVATE ${sources})

install(TARGETS merizo 
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if (DEFINED TESTS AND NOT TESTS EQUAL 0)
  add_subdirectory("test")
endif()



