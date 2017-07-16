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

add_executable(calculator ${src_files})

# Generate test runners for each file and generate test executables.
foreach(test_file ${test_files})
  get_filename_component(test_file_name ${test_file} NAME) # Strip path
  string(REGEX REPLACE "\\.[^.]*$" "" test_file_no_ext ${test_file_name}) # Remove extension
  set(test_runner_file_name ${test_file_no_ext}_runner.c)
  set(test_binary ${test_file_no_ext})
  # test files have the format "test_myfile.c" for testing the "myfile.c" source file.
  string(REPLACE "_" ";" test_file_duo ${test_file_no_ext}) # Find the source name
  list(GET test_file_duo 1 src_file_no_ext)		    # by splitting the test file
  set(src_file_name ${src_file_no_ext}.c)		    # Build the source file name.
  
  add_custom_command(
    OUTPUT  ${runners_dir}/${test_runner_file_name}
    DEPENDS ${test_file} ${src_dir}/${src_file_name}
    COMMAND ruby
            ${unity_root}/auto/generate_test_runner.rb
	    ${test_file}
	    ${runners_dir}/${test_runner_file_name}
    COMMENT "generate unity test runner"
    )

  add_executable(${test_binary}
    ${runners_dir}/${test_runner_file_name}
    ${src_dir}/${src_file_name}
    ${test_file}
    ${unity_src}
    )
endforeach()

# set_target_properties(whateverrr PROPERTIES
#   COMPILE_FLAGS "-Wall")




