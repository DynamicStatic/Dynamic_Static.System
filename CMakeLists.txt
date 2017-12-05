
# CMake configuration for Dynamic_Static.System
cmake_minimum_required(VERSION 3.3)
set(Dynamic_Static.cmake "${CMAKE_BINARY_DIR}/Dynamic_Static.cmake")
file(
    DOWNLOAD
    https://raw.githubusercontent.com/DynamicStatic/Dynamic_Static.CMake/master/Dynamic_Static.cmake
    ${Dynamic_Static.cmake}
)

include(${Dynamic_Static.cmake})
include("D:/Dynamic_Static/Dynamic_Static.CMake/Dynamic_Static_ex.cmake")
include("D:/Dynamic_Static/Dynamic_Static.CMake/Dynamic_Static.external.cmake")
dst_create_project_ex(Dynamic_Static.System)
################################################################################

# dst_build_external_package_exx(
#     target glfw
#     configuration "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw.cmake"
# )
################################################################################

################################################################################

################################################################################

################################################################################
include("${CMAKE_CURRENT_SOURCE_DIR}/external/Dynamic_Static.Core.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/external/glew.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/external/glfw.cmake")
set(includePath "${CMAKE_CURRENT_SOURCE_DIR}/include/Dynamic_Static/System/")
set(sourcePath "${CMAKE_CURRENT_SOURCE_DIR}/source/Dynamic_Static/System/")
dst_add_static_library_ex(
    target Dynamic_Static.System
    includeDirectories
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        ${Dynamic_Static.Core.includeDirectories}
        ${glfw.includeDirectories}
        $<$<PLATFORM_ID:Windows>:${glew.includeDirectories}>

    linkLibraries
        ${Dynamic_Static.Core.linkLibraries}
        ${glfw.linkLibraries}
        $<$<PLATFORM_ID:Windows>:${glew.linkLibraries}>

    includeFiles
        ${includePath}/Audio/AudioTest.hpp
        ${includePath}/Input/Keyboard.hpp
        ${includePath}/Input/Mouse.hpp
        ${includePath}/Application.hpp
        ${includePath}/Defines.hpp
        ${includePath}/GLInclude.hpp
        ${includePath}/Input.hpp
        ${includePath}/Monitor.hpp
        ${includePath}/Object.hpp
        ${includePath}/Resolution.hpp
        ${includePath}/Window.hpp

    sourceFiles
        ${sourcePath}/Audio/AudioTest.cpp
        ${sourcePath}/Input/Keyboard.cpp
        ${sourcePath}/Input/Mouse.cpp
        ${sourcePath}/Application.cpp
        ${sourcePath}/GLFWInclude.hpp
        ${sourcePath}/Monitor.cpp
        ${sourcePath}/Object.cpp
        ${sourcePath}/Resolution.cpp
        ${sourcePath}/Window.cpp
)
























# 
# # CMake configuration for Dynamic_Static.System
# cmake_minimum_required(VERSION 3.3)
# 
# set(Dynamic_Static.cmake "${CMAKE_BINARY_DIR}/Dynamic_Static.cmake")
# file(
#     DOWNLOAD
#     https://raw.githubusercontent.com/DynamicStatic/Dynamic_Static.CMake/master/Dynamic_Static.cmake
#     ${Dynamic_Static.cmake}
# )
# 
# include(${Dynamic_Static.cmake})
# dst_create_project(Dynamic_Static.System)
# set(CMAKE_CXX_STANDARD 14)
# if(MSVC)
#     option(BUILD_AUDIO_SUPPORT "Build audio support" ON)
# else()
#     option(BUILD_AUDIO_SUPPORT "Build audio support" OFF)
# endif()
# add_subdirectory("source/")
# 
# option(BUILD_EXAMPLES "Build Dynamic_Static.System examples" ON)
# if (BUILD_EXAMPLES)
#     add_subdirectory("examples/")
# endif()
# 
# option(BUILD_TESTS "Build Dynamic_Static.System tests" ON)
# if (BUILD_TESTS)
#     add_subdirectory("tests/")
# endif()
# 