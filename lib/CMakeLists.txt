cmake_minimum_required(VERSION 3.4)

project(ncn-lib CXX)

file(GLOB sources_CXX ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/FindNETCDF.cmake)

add_library(${PROJECT_NAME} ${sources_CXX})
target_link_libraries(${PROJECT_NAME} ${NETCDF_CXX_LIBRARIES})
target_include_directories(${PROJECT_NAME}
	INTERFACE ${CMAKE_CURRENT_LIST_DIR}
	PRIVATE ${NETCDF_CXX_INCLUDE_DIRECTORIES}
)
