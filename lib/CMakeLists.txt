cmake_minimum_required(VERSION 3.4)

project(ncn CXX)

file(GLOB sources_CXX ${CMAKE_CURRENT_LIST_DIR}/*.cpp)


add_library(${PROJECT_NAME} ${sources_CXX})
target_include_directories(${PROJECT_NAME}
	INTERFACE ${CMAKE_CURRENT_LIST_DIR}
)
