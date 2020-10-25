
# ==========================================
#   Copyright (c) 2016-2020 dynamic_static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

# dynamic_static.system CMake configuration
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(dynamic_static.system VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 17)
set(dynamic_static "${CMAKE_CURRENT_LIST_DIR}/../")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/")
################################################################################
include("${CMAKE_CURRENT_LIST_DIR}/../dynamic_static.build/dynamic_static.cmake")
dst_add_subdirectory(dynamic_static.core)
################################################################################

# Options
option(DST_SYS_BUILD_EXAMPLES "TODO : Documentation" ON)

# External dependencies
set(externalDirectory "${CMAKE_CURRENT_LIST_DIR}/external/")
include(glfw)
include(imgui)
include(stb)
list(APPEND linkLibraries dynamic_static.core)
list(APPEND linkLibraries glfw)
list(
    APPEND externalIncludeDirectories
    "${imgui_includeDirectories}"
    "${stb_includeDirectory}"
)
list(APPEND externalSourceFiles "${imgui_sourceFiles}")
if (MSVC)
    include(glew)
    list(APPEND externalIncludeDirectories "${glew_includeDirectories}")
    list(APPEND externalSourceFiles "${glew_sourceFiles}")
    list(APPEND externalCompileDefinitions "${glew_compileDefinitions}")
    list(APPEND linkLibraries glu32 opengl32)
else()
    list(APPEND linkLibraries
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

# dynamic_static.system library
set(includeDirectory "${CMAKE_CURRENT_LIST_DIR}/include/")
set(includePath "${includeDirectory}/dynamic_static/system/")
set(sourcePath "${CMAKE_CURRENT_LIST_DIR}/source/dynamic_static/system/")
dst_add_static_library(
    target dynamic_static.system
    linkLibraries "${linkLibraries}"
    compileDefinitions "${externalCompileDefinitions}"
    includeDirectories
        "${externalIncludeDirectories}"
        "${includeDirectory}"
    includeFiles
        "${includePath}/opengl/buffer.hpp"
        "${includePath}/opengl/defines.hpp"
        "${includePath}/opengl/gui.hpp"
        "${includePath}/opengl/index-buffer.hpp"
        "${includePath}/opengl/mesh.hpp"
        "${includePath}/opengl/object.hpp"
        "${includePath}/opengl/program.hpp"
        "${includePath}/opengl/shader.hpp"
        "${includePath}/opengl/texture.hpp"
        "${includePath}/opengl/vertex-array.hpp"
        "${includePath}/opengl/vertex-buffer.hpp"
        "${includePath}/opengl/vertex.hpp"
        "${includePath}/defines.hpp"
        "${includePath}/gamepad.hpp"
        "${includePath}/gui.hpp"
        "${includePath}/image.hpp"
        "${includePath}/input.hpp"
        "${includePath}/keyboard.hpp"
        "${includePath}/mouse.hpp"
        "${includePath}/opengl.hpp"
        "${includePath}/window.hpp"
        "${includeDirectory}/dynamic_static.system.hpp"
    sourceFiles
        "${externalSourceFiles}"
        "${sourcePath}/opengl/buffer.cpp"
        "${sourcePath}/opengl/gui.cpp"
        "${sourcePath}/opengl/index-buffer.cpp"
        "${sourcePath}/opengl/mesh.cpp"
        "${sourcePath}/opengl/object.cpp"
        "${sourcePath}/opengl/program.cpp"
        "${sourcePath}/opengl/shader.cpp"
        "${sourcePath}/opengl/shader.cpp"
        "${sourcePath}/opengl/texture.cpp"
        "${sourcePath}/opengl/vertex-array.cpp"
        "${sourcePath}/opengl/vertex-buffer.cpp"
        "${sourcePath}/gamepad.cpp"
        "${sourcePath}/glfw-window.hpp"
        "${sourcePath}/gui.cpp"
        "${sourcePath}/image.cpp"
        "${sourcePath}/input.cpp"
        "${sourcePath}/keyboard.cpp"
        "${sourcePath}/mouse.cpp"
        "${sourcePath}/window.cpp"
)

# Examples
if(DST_SYS_BUILD_EXAMPLES)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/examples/")
endif()
