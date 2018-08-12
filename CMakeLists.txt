
# ==========================================
#   Copyright (c) 2016-2018 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

# CMake configuration for Dynamic_Static.System

cmake_minimum_required(VERSION 3.3)
if(DEFINED ENV{DYNAMIC_STATIC_SDK})
    include("$ENV{DYNAMIC_STATIC_SDK}/Dynamic_Static.Cmake/.cmake")
else()
    include("external/Dynamic_Static.cmake/.cmake")
endif()
DstCreateProject(Dynamic_Static.System)

include("external/Dynamic_Static.Core.cmake")
include("external/FMOD.cmake")
include("external/glew.cmake")
include("external/glfw.cmake")
include("external/glm.cmake")
include("external/imgui.cmake")

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
        ${Dynamic_Static.Core.includeDirectories}
        ${FMOD.includeDirectories}
        ${glew.includeDirectories}
        ${glm.includeDirectories}
        ${imgui.includeDirectories}

    staticLibraries
        ${FMOD.staticLibraries}
        glfw
        ${glew.staticLibraries}
        ${systemLibraries}

    includeFiles
        "${includePath}/Audio/Defines.hpp"
        "${includePath}/Input/Keyboard.hpp"
        "${includePath}/Input/Mouse.hpp"
        "${includePath}/OpenGL/Buffer.hpp"
        "${includePath}/OpenGL/Defines.hpp"
        "${includePath}/OpenGL/IndexBuffer.hpp"
        "${includePath}/OpenGL/Mesh.hpp"
        "${includePath}/OpenGL/Object.hpp"
        "${includePath}/OpenGL/Program.hpp"
        "${includePath}/OpenGL/Shader.hpp"
        "${includePath}/OpenGL/State.hpp"
        "${includePath}/OpenGL/Texture.hpp"
        "${includePath}/OpenGL/Vertex.hpp"
        "${includePath}/OpenGL/VertexArray.hpp"
        "${includePath}/OpenGL/VertexBuffer.hpp"
        "${includePath}/Video/GLFW.hpp"
        "${includePath}/Video/GLFWWindow.hpp"
        "${includePath}/Video/Gui.hpp"
        "${includePath}/Video/Resolution.hpp"
        "${includePath}/Video/Window.hpp"
        "${includePath}/Video/Window.hpp"
        "${includePath}/Audio.hpp"
        "${includePath}/Defines.hpp"
        "${includePath}/Input.hpp"
        "${includePath}/OpenGL.hpp"
        "${includePath}/Video.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include.ex/Dynamic_Static.System.hpp"

    sourceFiles
        "${CMAKE_CURRENT_LIST_DIR}/ForceCMakeBuild.cpp"
)

option(BUILD_EXAMPLES "" ON)
if(BUILD_EXAMPLES)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/examples.ex/")
endif()
