
# ==========================================
#   Copyright (c) 2016-2020 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

# Dynamic_Static.System CMake configuration
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(Dynamic_Static.System VERSION 0.2.0)
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/")
set(externalDirectory "${CMAKE_CURRENT_LIST_DIR}/external/")

# Options
option(DST_SYS_BUILD_EXAMPLES "TODO : Documentation" ON)

# External dependencies
add_subdirectory("${externalDirectory}/Dynamic_Static.Core/")
include(glfw)
include(imgui)
list(APPEND linkLibraries Dynamic_Static.Core)
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
set(includePath "${includeDirectory}/dynamic_static/system/")
set(sourcePath "${CMAKE_CURRENT_LIST_DIR}/source.ex/dynamic_static/system/")
DstAddStaticLibrary(
    target Dynamic_Static.System
    folder Dynamic_Static.System/
    linkLibraries "${linkLibraries}"
    compileDefinitions "${externalCompileDefinitions}"
    includeDirectories
        "${externalIncludeDirectories}"
        "${includeDirectory}"


        "${CMAKE_CURRENT_LIST_DIR}/include/"

    includeFiles
        "${includePath}/input/keyboard.hpp"
        "${includePath}/input/mouse.hpp"
        "${includePath}/opengl/buffer.hpp"
        "${includePath}/opengl/defines.hpp"
        "${includePath}/opengl/gui.hpp"
        "${includePath}/opengl/index-buffer.hpp"
        "${includePath}/opengl/mesh.hpp"
        "${includePath}/opengl/object.hpp"
        "${includePath}/opengl/program.hpp"
        "${includePath}/opengl/shader.hpp"
        "${includePath}/opengl/shader.hpp"
        "${includePath}/opengl/texture.hpp"
        "${includePath}/opengl/vertex.hpp"
        "${includePath}/opengl/vertex-array.hpp"
        "${includePath}/opengl/vertex-buffer.hpp"
        "${includePath}/defines.hpp"
        "${includePath}/gui.hpp"
        "${includePath}/input.hpp"
        "${includePath}/opengl.hpp"
        "${includePath}/window.hpp"
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
        "${sourcePath}/input/keyboard.cpp"
        "${sourcePath}/input/mouse.cpp"
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
        "${sourcePath}/glfw-window.hpp"
        "${sourcePath}/gui.cpp"
        "${sourcePath}/input.cpp"
        "${sourcePath}/window.cpp"






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
