
# CMake configuration for Dynamic_Static.System

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/Dynamic_Static/System/)
set(INCLUDE_FILES
    ${INCLUDE_PATH}/Input/Keyboard.hpp
    ${INCLUDE_PATH}/Input/Mouse.hpp
    ${INCLUDE_PATH}/Application.hpp
    ${INCLUDE_PATH}/Defines.hpp
    ${INCLUDE_PATH}/GLInclude.hpp
    ${INCLUDE_PATH}/Input.hpp
    ${INCLUDE_PATH}/Monitor.hpp
    ${INCLUDE_PATH}/Object.hpp
    ${INCLUDE_PATH}/Resolution.hpp
    ${INCLUDE_PATH}/Window.hpp
)

set(SOURCE_PATH ${PROJECT_SOURCE_DIR}/source/Dynamic_Static/System)
set(SOURCE_FILES
    ${SOURCE_PATH}/Input/Input.cpp
    ${SOURCE_PATH}/Input/Input.Manager.cpp
    ${SOURCE_PATH}/Input/Keyboard.cpp
    ${SOURCE_PATH}/Input/Mouse.cpp
    ${SOURCE_PATH}/Application.cpp
    ${SOURCE_PATH}/GLFWInclude.hpp
    ${SOURCE_PATH}/Monitor.cpp
    ${SOURCE_PATH}/Object.cpp
    ${SOURCE_PATH}/Resolution.cpp
    ${SOURCE_PATH}/Window.cpp
)

dst_create_static_library("${INCLUDE_FILES}" "${SOURCE_FILES}")
# dst_create_shared_library("${INCLUDE_FILES}" "${SOURCE_FILES}")

if (MSVC)
    set(PLATFORM_SPECIFIC_INCLUDE_DEPENDENCIES
        ${glew.INCLUDE}
    )

    set(PLATFORM_SPECIFIC_LIBRARY_DEPENDENCIES
        glu32.lib
        opengl32.lib
        ${glew.LIBRARY}
    )
else()
    set(PLATFORM_SPECIFIC_INCLUDE_DEPENDENCIES)
    set(PLATFORM_SPECIFIC_LIBRARY_DEPENDENCIES
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
    PUBLIC ${PLATFORM_SPECIFIC_INCLUDE_DEPENDENCIES}
    PUBLIC ${Dynamic_Static.Core.INCLUDE}
    PUBLIC ${glfw.INCLUDE}
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    PUBLIC ${PLATFORM_SPECIFIC_LIBRARY_DEPENDENCIES}
    # PUBLIC Dynamic_Static.Core
    PUBLIC ${Dynamic_Static.Core.LIBRARY}
    PUBLIC ${glfw.LIBRARY}
    # PUBLIC ${PLATFORM_SPECIFIC_LIBRARY_DEPENDENCIES}
)

# dst_install_library()
