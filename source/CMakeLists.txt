
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

add_library(${CMAKE_PROJECT_NAME} STATIC ${includeFiles} ${sourceFiles})
include("${CMAKE_SOURCE_DIR}/external/Dynamic_Static.Core.cmake")
include("${CMAKE_SOURCE_DIR}/external/glew.cmake")
include("${CMAKE_SOURCE_DIR}/external/glfw.cmake")
add_dependencies(${CMAKE_PROJECT_NAME} Dynamic_Static.Core.package)
add_dependencies(${CMAKE_PROJECT_NAME} glfw)
dst_create_static_library("${includeFiles}" "${sourceFiles}")
# dst_create_shared_library("${includeFiles}" "${sourceFiles}")

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

# NOTE : There shouldn't be a need to list Dynamic_Static.Core.INCLUDE here...
#        Adding `PUBLIC Dynamic_Static.Core` to target_link_libraries() should
#        take care of the include as well...it does, in fact compile, the issue
#        is that for whatever reason it doesn't add the includes to the target's
#        INCLUDE_DIRECTORIES property which is what we're using to forward the
#        includes to the final build target...this seems like an oversight.
target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC ${platformSpecificIncludeDependencies}
    PUBLIC ${glfw.include}
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PUBLIC ${platformSpecificLibraryDependencies}
    PUBLIC Dynamic_Static.Core
    PUBLIC ${glfw.library}
    # PUBLIC ${platformSpecificLibraryDependencies}
)

# dst_install_library("${Dynamic_Static.Core.includeDirectories}")

# message("Dynamic_Static.Core include directories")
# foreach(includeDirectory ${Dynamic_Static.Core.includeDirectories})
#     message("    ${includeDirectory}")
# endforeach()

# if (# EXISTS Dynamic_Static.Core AND
#     EXISTS glfw)
    # add_dependencies(${CMAKE_PROJECT_NAME} Dynamic_Static.Core)
    # add_dependencies(${CMAKE_PROJECT_NAME} glfw)
    
    ############ # if (EXISTS ${Dynamic_Static.Core.configuration})
    ############ # include(${Dynamic_Static.Core.configuration})
    ############ message("hit")
    ############ get_property(
    ############     Dynamic_Static.Core.addtionalIncludeDirectories
    ############     TARGET ${Dynamic_Static.Core}
    ############     PROPERTY INCLUDE_DIRECTORIES
    ############ )
    ############ foreach(additionalIncludeDirectory ${Dynamic_Static.Core.addtionalIncludeDirectories})
    ############     message("additionalIncludeDirectory=${additionalIncludeDirectory}")
    ############ endforeach()
    ############ # endif()
# endif()

# dst_install_library()
