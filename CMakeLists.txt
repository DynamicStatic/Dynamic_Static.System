
# ==========================================
#   Copyright (c) 2016-2020 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

# Dynamic_Static.System CMake configuration
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(Dynamic_Static.System VERSION 2.0.0)
set(CMAKE_CXX_STANDARD 17)
set(dynamic_static "${CMAKE_CURRENT_LIST_DIR}/../")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/")
include("${dynamic_static}/Dynamic_Static.CMake/Dynamic_Static.ex.cmake")
DstAddSubdirectory("Dynamic_Static.Core")

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
    list(APPEND linkLibraries
        glu32
        opengl32
    )
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

# Dynamic_Static.System library
set(includeDirectory "${CMAKE_CURRENT_LIST_DIR}/include.ex/")
set(graphicsIncludePath "${includeDirectory}/dynamic_static/graphics/")
set(systemIncludePath "${includeDirectory}/dynamic_static/system/")
set(graphicsSourcePath "${CMAKE_CURRENT_LIST_DIR}/source.ex/dynamic_static/graphics/")
set(systemSourcePath "${CMAKE_CURRENT_LIST_DIR}/source.ex/dynamic_static/system/")
DstAddStaticLibrary(
    target dynamic_static.system
    linkLibraries "${linkLibraries}"
    compileDefinitions "${externalCompileDefinitions}"
    includeDirectories
        "${externalIncludeDirectories}"
        "${includeDirectory}"


        "${CMAKE_CURRENT_LIST_DIR}/include/"

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









        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Image/Image.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Image/ManagedImage.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Image/UnmanagedImage.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Image/WriteableImage.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Image/WriteableUnmanagedImage.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Input/Keyboard.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Input/Mouse.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Buffer.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Defines.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Gui.Renderer.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/IndexBuffer.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Mesh.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Object.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Program.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Shader.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/State.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Texture.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Vertex.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/VertexArray.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/VertexBuffer.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Text/Font.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Text/Font.Atlas.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Text/Glyph.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Text/Layout.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Audio.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Defines.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Format.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Gui.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Image.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Input.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Text.ex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Window.ex.hpp"






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






        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Image/Image.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Image/ManagedImage.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Image/UnmanagedImage.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Image/WriteableUnmanagedImage.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Input/Keyboard.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Input/Mouse.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Text/Font.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Text/Font.Atlas.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Text/Glyph.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Format.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/GlfwWindow.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Gui.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Image.ex.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Input.ex.cpp"
)

# Examples
if(DST_SYS_BUILD_EXAMPLES)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/examples.ex/")
endif()
