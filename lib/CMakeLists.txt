cmake_minimum_required(VERSION 3.4)

project(ncn-lib CXX)

file(GLOB sources_CXX ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
file(GLOB headers_CXX ${CMAKE_CURRENT_LIST_DIR}/*.h) # make it more convenient in IDEs like Xcode

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/FindNETCDF.cmake)

add_library(${PROJECT_NAME} ${sources_CXX} ${headers_CXX})
target_link_libraries(${PROJECT_NAME} ${NETCDF_CXX_LIBRARIES})
target_include_directories(${PROJECT_NAME}
   INTERFACE ${CMAKE_CURRENT_LIST_DIR}
   PRIVATE ${NETCDF_CXX_INCLUDE_DIRECTORIES} # we do not expose the netcdf API, so we do not need to forward the include dir
)
if(${CMAKE_CXX_COMPILER_ID} STREQUAL Cray )
   target_compile_options(${PROJECT_NAME} PRIVATE -hstd=c++11)
else()
   set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11) # does not work for cray: sets "-std=c++11" for the crayc++ compiler, which needs to have "-hstd=c++11"
endif()
