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
if(${CMAKE_CXX_COMPILER_ID} STREQUAL Cray )
   target_compile_options(${PROJECT_NAME} PRIVATE -hstd=c++11)
else()
   set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11) # does not work for cray: sets "-std=c++11" for the crayc++ compiler, which needs to have "-hstd=c++11"
endif()

# test
add_subdirectory(test/googletest_0a43962 ${PROJECT_BINARY_DIR}/gtest)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/FindNETCDF.cmake)

file(GLOB sources_CXX ${CMAKE_CURRENT_LIST_DIR}/test/*.cpp)
add_executable(${PROJECT_NAME}-tests ${sources_CXX})
target_link_libraries(${PROJECT_NAME}-tests ncn-lib gtest ${NETCDF_CXX_LIBRARIES})
target_include_directories(${PROJECT_NAME}-tests
   PRIVATE ${NETCDF_CXX_INCLUDE_DIRECTORIES}
)
if(${CMAKE_CXX_COMPILER_ID} STREQUAL Cray )
   target_compile_options(${PROJECT_NAME}-tests PRIVATE -hstd=c++11)
else()
   set_property(TARGET ${PROJECT_NAME}-tests PROPERTY CXX_STANDARD 11) # does not work for cray: sets "-std=c++11" for the crayc++ compiler, which needs to have "-hstd=c++11"
endif()
