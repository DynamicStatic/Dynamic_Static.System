
dst_add_external_package(
    Dynamic_Static.Core
    "${PROJECT_SOURCE_DIR}/external/Dynamic_Static.Core.cmake"
)

include("${PROJECT_SOURCE_DIR}/external/glew.cmake")
include("${PROJECT_SOURCE_DIR}/external/glfw.cmake")

set(includePath ${PROJECT_SOURCE_DIR}/include/Dynamic_Static/System/)
set(includeFiles
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
)

set(sourcePath ${PROJECT_SOURCE_DIR}/source/Dynamic_Static/System)
set(sourceFiles
    ${sourcePath}/Input/Input.cpp
    ${sourcePath}/Input/Input.Manager.cpp
    ${sourcePath}/Input/Keyboard.cpp
    ${sourcePath}/Input/Mouse.cpp
    
    ${sourcePath}/Application.cpp
    ${sourcePath}/GLFWInclude.hpp
    ${sourcePath}/Monitor.cpp
    ${sourcePath}/Object.cpp
    ${sourcePath}/Resolution.cpp
    ${sourcePath}/Window.cpp
)

add_library(${CMAKE_PROJECT_NAME} STATIC "${includeFiles}" "${sourceFiles}")
set_target_properties(
    ${CMAKE_PROJECT_NAME}
    PROPERTIES
        LINK_FLAGS "-fPIC"
)

add_dependencies(${CMAKE_PROJECT_NAME} Dynamic_Static.Core)
add_dependencies(${CMAKE_PROJECT_NAME} glfw)
dst_setup_target(${CMAKE_PROJECT_NAME} "${includeFiles}" "${sourceFiles}")

if (MSVC)
    set(platformSpecificIncludeDependencies
        ${glew.include}
    )

    set(platformSpecificLibraryDependencies
        glu32.lib
        opengl32.lib
        ${glew.library}
    )
else()
    set(platformSpecificIncludeDependencies)
    set(platformSpecificLibraryDependencies
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

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC ${platformSpecificIncludeDependencies}
    PUBLIC ${Dynamic_Static.Core.includeDirectories}
    PUBLIC ${glfw.include}
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PUBLIC INTERFACE ${platformSpecificLibraryDependencies}
    PUBLIC INTERFACE ${Dynamic_Static.Core.linkLibraries}
    PUBLIC INTERFACE ${glfw.library}
)

dst_export_target(${CMAKE_PROJECT_NAME})
