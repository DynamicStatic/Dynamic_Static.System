
cmake_minimum_required(VERSION 3.3)
include(ExternalProject)
ExternalProject_Add(
    Dynamic_Static.Core
    URL https://github.com/DynamicStatic/Dynamic_Static.Core/archive/master.zip
    BINARY_DIR build
    CMAKE_ARGS
        -DBUILD_SANDBOX=OFF
        -DBUILD_TESTS=OFF
    INSTALL_COMMAND ""
)
