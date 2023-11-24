cmake_minimum_required(VERSION 3.2)

project(reflection_test)

set(CMAKE_CXX_STANDARD 17)

list(PREPEND CMAKE_MODULE_PATH 
    ${CMAKE_CURRENT_SOURCE_DIR}/target_data
)
include(libProtobuf)
include(target_data)

add_executable(reflection_test main.cpp)
target_link_libraries(reflection_test target_data)
target_compile_definitions(reflection_test INTERFACE -DTEST_DATA_PATH="${reflection_test_SOURCE_DIR}/test_data")
