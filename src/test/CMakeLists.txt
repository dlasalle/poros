function(setup_test test_file)
  file(GLOB source ${test_file}.cpp)
	add_executable(${test_file} ${test_file})
	target_link_libraries(${test_file} wildriver)
	add_test(NAME ${test_file} COMMAND ${test_file})
endfunction()


include_directories(.)


file(GLOB files "*_test.cpp")
foreach(file ${files})
  get_filename_component(basename "${file}" NAME_WE)
  setup_test(${basename})
endforeach()

