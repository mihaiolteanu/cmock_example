cmake_minimum_required(VERSION 3.8.0)
project(unity_examples)

set(UNITY_ROOT  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/Unity)
set(SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(RUNNERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test/test_runners)
set(BUILD_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/build)
file(GLOB SOURCE_FILES  "${SOURCE_DIR}/*.c")
file(GLOB TEST_FILES    "${TEST_DIR}/*.c")
file(GLOB RUNNERS_FILES "${RUNNERS_DIR}/*.c")
set(UNITY_SRC ${UNITY_ROOT}/src/unity.c)
include_directories(src ${UNITY_ROOT}/src)

foreach(file ${TEST_FILES})
  get_filename_component(RUNNER ${file} NAME)
  execute_process(
    COMMAND ruby ${UNITY_ROOT}/auto/generate_test_runner.rb ${file} ${RUNNERS_DIR}/${RUNNER}
    )
endforeach()

add_executable(add_test ${RUNNERS_DIR}/test_add.c ${SOURCE_DIR}/add.c ${TEST_DIR}/test_add.c ${UNITY_SRC})

# add_custom_command(
#   OUTPUT            ${RUNNERS_DIR}/test_add_runner.c
#   DEPENDS           ${SOURCE_DIR}/add.c
#   COMMAND           ruby
#                     ${UNITY_ROOT}/auto/generate_test_runner.rb
#                     ${TEST_DIR/}test_add.c
# 		    ${RUNNERS_DIR}/test_add_runner.c
#   --framework="unity/unity"
#   # WORKING_DIRECTORY ${UNITY_TEST_SCRIPT_DIR}
#   COMMENT           "generate unity test runner"
# )

