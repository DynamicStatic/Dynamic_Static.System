
#==========================================
#    Copyright 2011-2018 Dynamic_Static
#        Patrick Purcell
#    Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

# CMake configuration for Dynamic_Static.System
cmake_minimum_required(VERSION 3.3)
option(SDK_BUILD "TODO : This shouldn't be the default" ON)
if(SDK_BUILD)
    include("$ENV{DYNAMIC_STATIC_SDK}/Dynamic_Static.CMake/.cmake")
else()
    include("external/Dynamic_Static.CMake/.cmake")
endif()
DstCreateProject(Dynamic_Static.System)

include("external/Dynamic_Static.Core.cmake")
include("external/glew.cmake")
include("external/glfw.cmake")
include("external/imgui.cmake")

if(MSVC)
    set(systemLinkLibraries
        glu32.lib
        opengl32.lib
    )
else()
    set(systemLinkLibraries
        EGL
        GL
        X11
        Xcursor
        Xi
        Xinerama
        Xrandr
        Xxf86vm
    )
endif()

set(includePath "${CMAKE_CURRENT_LIST_DIR}/include.ex/Dynamic_Static/System/")
set(sourcePath "${CMAKE_CURRENT_LIST_DIR}/source.ex/Dynamic_Static/System/")
DstCreateStaticLibrary(
    target Dynamic_Static.System
    includeDirectories
        "${CMAKE_CURRENT_LIST_DIR}/include.ex/"
        ${glew.includeDirectories}
        ${imgui.includeDirectories}

    staticLinkLibraries
        Dynamic_Static.Core
        glfw
        ${glew.staticLinkLibraries}
        ${systemLinkLibraries}

    includeFiles
        ${includePath}/Defines.hpp
        ${includePath}/OpenGL.hpp
        ${includePath}/Window.hpp

    sourceFiles
        ${sourcePath}/GLFWWindow.cpp
        ${sourcePath}/Window.cpp
)

option(BUILD_TESTS "Build Dynamic_Static.System.Tests" OFF)
if(BUILD_TESTS)
    set(testsPath "${CMAKE_CURRENT_LIST_DIR}/tests.ex/")
    DstCreateTests(
        target Dynamic_Static.System
        sourceFiles
    )
endif()

option(BUILD_EXAMPLES "" ON)
if(BUILD_EXAMPLES)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/examples.ex/")
endif()
