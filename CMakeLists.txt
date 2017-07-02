cmake_minimum_required(VERSION 3.8.0)
project(unity_examples)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build) # Location of executables
set(UNITY_ROOT  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/Unity)
set(SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(RUNNERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test/test_runners)
set(UNITY_SRC   ${UNITY_ROOT}/src/unity.c)
file(GLOB SOURCE_FILES    "${SOURCE_DIR}/*.c")
file(GLOB TEST_FILES    "${TEST_DIR}/*.c")
include_directories(${SOURCE_DIR} ${UNITY_ROOT}/src)

add_executable(calculator ${SOURCE_FILES})

# Generate test runners for each file and generate test executables.
foreach(TEST_FILE ${TEST_FILES})
  get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME) # Strip path
  string(REGEX REPLACE "\\.[^.]*$" "" TEST_FILE_NO_EXT ${TEST_FILE_NAME}) # Remove extension
  set(TEST_RUNNER_FILE_NAME ${TEST_FILE_NO_EXT}_runner.c)
  set(TEST_BINARY ${TEST_FILE_NO_EXT})
  # test files have the format "test_myfile.c" for testing the "myfile.c" source file.
  string(REPLACE "_" ";" TEST_FILE_DUO ${TEST_FILE_NO_EXT}) # Find the source name
  list(GET TEST_FILE_DUO 1 SOURCE_FILE_NO_EXT)		    # by splitting the test file
  set(SOURCE_FILE_NAME ${SOURCE_FILE_NO_EXT}.c)		    # Build the source file name.
  # message(${SOURCE_FILE_NO_EXT})

  add_custom_command(
    OUTPUT  ${RUNNERS_DIR}/${TEST_RUNNER_FILE_NAME}
    DEPENDS ${TEST_FILE} ${SOURCE_DIR}/${SOURCE_FILE_NAME}
    COMMAND ruby
            ${UNITY_ROOT}/auto/generate_test_runner.rb
	    ${TEST_FILE}
	    ${RUNNERS_DIR}/${TEST_RUNNER_FILE_NAME}
    COMMENT "generate unity test runner"
    )

  add_executable(${TEST_BINARY}
    ${RUNNERS_DIR}/${TEST_RUNNER_FILE_NAME}
    ${SOURCE_DIR}/${SOURCE_FILE_NAME}
    ${TEST_FILE}
    ${UNITY_SRC}
    )
endforeach()

# set_target_properties(whateverrr PROPERTIES
#   COMPILE_FLAGS "-Wall")




