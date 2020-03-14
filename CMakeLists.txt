
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
list(APPEND linkLibraries Dynamic_Static.Core)
include(glfw)
list(APPEND linkLibraries glfw)
if (MSVC)
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
    linkLibraries ${linkLibraries}
    includeDirectories
        "${includeDirectory}"

        "${CMAKE_CURRENT_LIST_DIR}/include/"

    includeFiles
        "${includePath}/opengl/buffer.hpp"
        "${includePath}/opengl/defines.hpp"
        "${includePath}/opengl/index-buffer.hpp"
        "${includePath}/opengl/mesh.hpp"
        "${includePath}/opengl/object.hpp"
        "${includePath}/opengl/program.hpp"
        "${includePath}/opengl/shader.hpp"
        "${includePath}/opengl/shader.hpp"
        "${includePath}/opengl/texture.hpp"
        "${includePath}/opengl/vertex-array.hpp"
        "${includePath}/opengl/vertex-buffer.hpp"
        "${includePath}/defines.hpp"
        "${includePath}/opengl.hpp"
        "${includePath}/window.hpp"









        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Image/Image.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Image/ManagedImage.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Image/UnmanagedImage.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Image/WriteableImage.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Image/WriteableUnmanagedImage.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Input/Keyboard.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Input/Mouse.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Buffer.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Defines.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Gui.Renderer.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/IndexBuffer.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Mesh.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Object.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Program.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Shader.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/State.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Texture.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/Vertex.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/VertexArray.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL/VertexBuffer.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Text/Font.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Text/Font.Atlas.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Text/Glyph.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Text/Layout.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Audio.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Defines.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Format.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Gui.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Image.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Input.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/OpenGL.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Text.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/include/Dynamic_Static/System/Window.hpp"






    sourceFiles
        "${sourcePath}/opengl/buffer.cpp"
        "${sourcePath}/opengl/index-buffer.cpp"
        "${sourcePath}/opengl/mesh.cpp"
        "${sourcePath}/opengl/object.cpp"
        "${sourcePath}/opengl/program.cpp"
        "${sourcePath}/opengl/shader.cpp"
        "${sourcePath}/opengl/shader.cpp"
        "${sourcePath}/opengl/texture.cpp"
        "${sourcePath}/opengl/vertex-array.cpp"
        "${sourcePath}/opengl/vertex-buffer.cpp"
        "${sourcePath}/window.cpp"






        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Image/Image.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Image/ManagedImage.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Image/UnmanagedImage.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Image/WriteableUnmanagedImage.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Input/Keyboard.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Input/Mouse.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Text/Font.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Text/Font.Atlas.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Text/Glyph.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Format.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/GlfwWindow.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Gui.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Image.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/source/Dynamic_Static/System/Input.cpp"
)

# Examples
if(DST_SYS_BUILD_EXAMPLES)
    # add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/examples.ex/")
endif()
