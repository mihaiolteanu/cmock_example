cmake_minimum_required(VERSION 3.8.0)
project(unity_examples)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build) # Location of executables
set(unity_root  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/Unity)
set(src_dir     ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(test_dir    ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(runners_dir ${CMAKE_CURRENT_SOURCE_DIR}/test/test_runners)
set(unity_src   ${unity_root}/src/unity.c)
file(GLOB src_files  "${src_dir}/*.c")
file(GLOB test_files "${test_dir}/test_*.c")
include_directories(${src_dir} ${unity_root}/src)

function(set_file_names file src runner binary)
  get_filename_component(file_name ${file} NAME) # Strip path
  string(REGEX REPLACE "\\.[^.]*$" "" file_noext ${file_name}) # Remove extension
  set(${runner} ${file_noext}_runner.c PARENT_SCOPE)
  set(${binary} ${file_noext} PARENT_SCOPE)
  # test files have the format "test_myfile.c" for testing the "myfile.c" source file.
  string(REPLACE "_" ";" split ${file_noext})
  list(GET split 1 src_noext)
  set(${src} ${src_noext}.c PARENT_SCOPE)
endfunction(set_file_names)

add_executable(calculator ${src_files})

# Generate test runners for each file and generate test executables.
foreach(test ${test_files})
  set_file_names(${test} src runner binary)
  
  add_custom_command(
    OUTPUT  ${runners_dir}/${runner}
    DEPENDS ${test} ${src_dir}/${src}
    COMMAND ruby
            ${unity_root}/auto/generate_test_runner.rb
	    ${test}
	    ${runners_dir}/${runner}
    COMMENT "generate unity test runner"
    )

  add_executable(${binary}
    ${runners_dir}/${runner}
    ${src_dir}/${src}
    ${test}
    ${unity_src}
    )
endforeach()

# set_target_properties(whateverrr PROPERTIES
#   COMPILE_FLAGS "-Wall")
