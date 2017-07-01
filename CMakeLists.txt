cmake_minimum_required(VERSION 3.8.0)
project(unity_examples)

include_directories(src)
set(UNITY_ROOT  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/Unity)
set(SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(RUNNERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test/test_runners)
set(BUILD_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/build)
file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.c")
file(GLOB TEST_FILES   "${TEST_DIR}/*.c")

add_custom_command(
  OUTPUT            ${RUNNERS_DIR}/test_add_runner.c
  DEPENDS           ${SOURCE_DIR}/add.c
  COMMAND           ruby
                    ${UNITY_ROOT}/auto/generate_test_runner.rb
                    ${TEST_DIR/}test_add.c
		    ${RUNNERS_DIR}/test_add_runner.c
  --framework="unity/unity"
  # WORKING_DIRECTORY ${UNITY_TEST_SCRIPT_DIR}
  COMMENT           "generate unity test runner"
)

