
# ==========================================
#   Copyright (c) 2016-2018 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

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
include("external/FMOD.cmake")
include("external/glew.cmake")
include("external/glfw.cmake")
# include("external/imgui.cmake")

if(MSVC)
    set(systemLibraries
        glu32.lib
        opengl32.lib
    )
else()
    set(systemLibraries
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
    folder Dynamic_Static.System/
    includeDirectories
        "${CMAKE_CURRENT_LIST_DIR}/include.ex/"
        ${FMOD.includeDirectories}
        ${glew.includeDirectories}
        # ${imgui.includeDirectories}

    staticLibraries
        Dynamic_Static.Core
        ${FMOD.staticLibraries}
        glfw
        ${glew.staticLibraries}
        ${systemLibraries}

    includeFiles
        ${CMAKE_CURRENT_LIST_DIR}/include.ex/Dynamic_Static.System.hpp
        ${includePath}/Audio/Defines.hpp
        ${includePath}/Input/Keyboard.hpp
        ${includePath}/Input/Mouse.hpp
        ${includePath}/Video/GLFW.hpp
        ${includePath}/Video/GLFWWindow.hpp
        ${includePath}/Video/Resolution.hpp
        ${includePath}/Video/Window.hpp
        ${includePath}/Video/Window.hpp
        ${includePath}/Audio.hpp
        ${includePath}/Defines.hpp
        ${includePath}/Input.hpp
        ${includePath}/OpenGL.hpp
        ${includePath}/Video.hpp

    sourceFiles
        ${sourcePath}/Placeholder.cpp
)

option(BUILD_TESTS "Build Dynamic_Static.System.Tests" OFF)
if(BUILD_TESTS)
    set(testsPath "${CMAKE_CURRENT_LIST_DIR}/tests.ex/")
    DstCreateTests(
        target Dynamic_Static.System
        folder Dynamic_Static.System/
        sourceFiles
    )
endif()

option(BUILD_EXAMPLES "" ON)
if(BUILD_EXAMPLES)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/examples.ex/")
endif()
