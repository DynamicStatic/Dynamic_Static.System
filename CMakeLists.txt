
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
list(APPEND linkLibraries dynamic_static.core)
list(APPEND linkLibraries glfw)
list(APPEND externalIncludeDirectories "${imgui_includeDirectories}")
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
set(graphicsIncludePath "${includeDirectory}/dynamic_static/graphics/")
set(systemIncludePath "${includeDirectory}/dynamic_static/system/")
set(graphicsSourcePath "${CMAKE_CURRENT_LIST_DIR}/source/dynamic_static/graphics/")
set(systemSourcePath "${CMAKE_CURRENT_LIST_DIR}/source/dynamic_static/system/")
dst_add_static_library(
    target dynamic_static.system
    linkLibraries "${linkLibraries}"
    compileDefinitions "${externalCompileDefinitions}"
    includeDirectories
        "${externalIncludeDirectories}"
        "${includeDirectory}"
    includeFiles
        "${graphicsIncludePath}/opengl/buffer.hpp"
        "${graphicsIncludePath}/opengl/defines.hpp"
        "${graphicsIncludePath}/opengl/gui.hpp"
        "${graphicsIncludePath}/opengl/index-buffer.hpp"
        "${graphicsIncludePath}/opengl/mesh.hpp"
        "${graphicsIncludePath}/opengl/object.hpp"
        "${graphicsIncludePath}/opengl/program.hpp"
        "${graphicsIncludePath}/opengl/shader.hpp"
        "${graphicsIncludePath}/opengl/texture.hpp"
        "${graphicsIncludePath}/opengl/vertex-array.hpp"
        "${graphicsIncludePath}/opengl/vertex-buffer.hpp"
        "${graphicsIncludePath}/opengl/vertex.hpp"
        "${systemIncludePath}/defines.hpp"
        "${systemIncludePath}/gamepad.hpp"
        "${systemIncludePath}/gui.hpp"
        "${systemIncludePath}/input.hpp"
        "${systemIncludePath}/keyboard.hpp"
        "${systemIncludePath}/mouse.hpp"
        "${systemIncludePath}/window.hpp"
        "${includeDirectory}/dynamic_static.graphics.opengl.hpp"
        "${includeDirectory}/dynamic_static.system.hpp"
    sourceFiles
        "${externalSourceFiles}"
        "${graphicsSourcePath}/opengl/buffer.cpp"
        "${graphicsSourcePath}/opengl/gui.cpp"
        "${graphicsSourcePath}/opengl/index-buffer.cpp"
        "${graphicsSourcePath}/opengl/mesh.cpp"
        "${graphicsSourcePath}/opengl/object.cpp"
        "${graphicsSourcePath}/opengl/program.cpp"
        "${graphicsSourcePath}/opengl/shader.cpp"
        "${graphicsSourcePath}/opengl/shader.cpp"
        "${graphicsSourcePath}/opengl/texture.cpp"
        "${graphicsSourcePath}/opengl/vertex-array.cpp"
        "${graphicsSourcePath}/opengl/vertex-buffer.cpp"
        "${systemSourcePath}/gamepad.cpp"
        "${systemSourcePath}/glfw-window.hpp"
        "${systemSourcePath}/gui.cpp"
        "${systemSourcePath}/input.cpp"
        "${systemSourcePath}/keyboard.cpp"
        "${systemSourcePath}/mouse.cpp"
        "${systemSourcePath}/window.cpp"
)

# Examples
if(DST_SYS_BUILD_EXAMPLES)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/examples/")
endif()
