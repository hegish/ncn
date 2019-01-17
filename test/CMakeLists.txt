cmake_minimum_required(VERSION 3.4)

project(test-ncn CXX)

add_subdirectory(../lib ${PROJECT_BINARY_DIR}/ncn)
add_subdirectory(googletest_0a43962 ${PROJECT_BINARY_DIR}/gtest)

file(GLOB sources_CXX ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${sources_CXX})
target_link_libraries(${PROJECT_NAME} ncn gtest)
target_compile_options(${PROJECT_NAME} PRIVATE -std=c++11)
