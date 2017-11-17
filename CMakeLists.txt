
# CMake configuration for Dynamic_Static.System
cmake_minimum_required(VERSION 3.2)
include("${PROJECT_SOURCE_DIR}/Dynamic_Static.cmake")
dst_create_project(Dynamic_Static.System)
add_subdirectory("source/")

# option(BUILD_EXAMPLES "Build Dynamic_Static.System examples" OFF)
# if (BUILD_EXAMPLES)
#     add_subdirectory("examples/")
# endif()
# 
# option(BUILD_TESTS "Build Dynamic_Static.System tests" OFF)
# if (BUILD_TESTS)
#     add_subdirectory("tests/")
# endif()
