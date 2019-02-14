cmake_minimum_required(VERSION 3.4)

project(ncn CXX)

# bin
add_subdirectory(lib ${PROJECT_BINARY_DIR}/ncn-lib)

file(GLOB sources_CXX ${CMAKE_CURRENT_LIST_DIR}/bin/*.cpp ${CMAKE_CURRENT_LIST_DIR}/bin/subcommand_line_interface/*.cpp)
add_executable(${PROJECT_NAME} ${sources_CXX})
target_link_libraries(${PROJECT_NAME} ncn-lib)
target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_CURRENT_LIST_DIR}/bin/subcommand_line_interface
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# test
add_subdirectory(test/googletest_0a43962 ${PROJECT_BINARY_DIR}/gtest)

file(GLOB sources_CXX ${CMAKE_CURRENT_LIST_DIR}/test/*.cpp)
add_executable(${PROJECT_NAME}-tests ${sources_CXX})
target_link_libraries(${PROJECT_NAME}-tests ncn-lib gtest)
set_property(TARGET ${PROJECT_NAME}-tests PROPERTY CXX_STANDARD 11)
