
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

list(APPEND external.staticLibraries
    glfw
    "${glew.staticLibraries}"
    "${systemLibraries}"
)
list(APPEND external.includeDirectories
    "${Dynamic_Static.Core.includeDirectories}"
    "${glew.includeDirectories}"
    "${glm.includeDirectories}"
    "${imgui.includeDirectories}"
)
option(BUILD_DST_SYS_AUDIO "Build Dynamic_Static.System.Audio" ON)
if(BUILD_DST_SYS_AUDIO)
    include("external/FMOD.cmake")
    if(${FMOD.available})
        list(APPEND external.staticLibraries "${FMOD.staticLibraries}")
        list(APPEND external.includeDirectories "${FMOD.includeDirectories}")
    else()
        set(BUILD_DST_SYS_AUDIO OFF)
    endif()
endif()

set(includePath "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/")
set(sourcePath "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/")
DstCreateStaticLibrary(
    target Dynamic_Static.System
    folder Dynamic_Static.System/
    
    staticLibraries
        "${external.staticLibraries}"
        
    includeDirectories
        "${external.includeDirectories}"
        "${CMAKE_CURRENT_LIST_DIR}/include/"
        
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
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static.System.hpp"

    sourceFiles
        "${imgui.sourceFiles}"
)

# TODO : Add compile definitions to DstCreateStaticLibrary()
if(BUILD_DST_SYS_AUDIO)
    target_compile_definitions(
        Dynamic_Static.System
        PUBLIC DYNAMIC_STATIC_SYSTEM_FMOD_ENABLED
    )
endif()

option(BUILD_DST_SYS_EXAMPLES "Build Dynamic_Static.System.Examples" ON)
if(BUILD_DST_SYS_EXAMPLES)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/examples/")
endif()
