
# CMake configuration for Dynamic_Static.System

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include/Dynamic_Static/System/)
set(INCLUDE_FILES
    ${INCLUDE_PATH}/Application.hpp
    ${INCLUDE_PATH}/Defines.hpp
    ${INCLUDE_PATH}/Monitor.hpp
    ${INCLUDE_PATH}/Object.hpp
    ${INCLUDE_PATH}/Resolution.hpp
    ${INCLUDE_PATH}/Window.hpp
)

set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Dynamic_Static/System)
set(SOURCE_FILES
    ${SOURCE_PATH}/Application.cpp
    ${SOURCE_PATH}/GLFWInclude.hpp
    ${SOURCE_PATH}/Monitor.cpp
    ${SOURCE_PATH}/Object.cpp
    ${SOURCE_PATH}/Resolution.cpp
    ${SOURCE_PATH}/Window.cpp
)

create_file_group("${INCLUDE_FILES}")
create_file_group("${SOURCE_FILES}")

if (MSVC)
    set(SYSTEM_INSTALL_DEPENDENCIES
    )
else()
    set(SYSTEM_INSTALL_DEPENDENCIES
        EGL
        X11
        Xcursor
        Xi
        Xinerama
        Xrandr
        Xxf86vm
        dl
        pthread
        stdc++fs
    )
endif()

set(TARGET Dynamic_Static.Graphics)
add_library(${TARGET} ${INCLUDE_FILES} ${SOURCE_FILES})
set_target_properties(Dynamic_Static.Graphics PROPERTIES PREFIX "")
# TODO : Why doesn't transitive linking work when we let CMake auto link and include Dynamic_Static.Core?
#        It's OK to do it explicitly for now, but this will need to be addressed sooner or later.
# NOTE : This comment is duplicated in Dynamic_Static.Core.cmake
# if (EXISTS ${Dynamic_Static.Core.PACKAGE})
    target_include_directories(
        ${TARGET}
        PUBLIC ${PROJECT_SOURCE_DIR}/include/
        PUBLIC ${Dynamic_Static.Core.INCLUDE}
        PUBLIC ${GLFW.INCLUDE}
    )

    # TODO : It's super annoying that order matters for listing link dependencies here...
    target_link_libraries(
        ${TARGET}
        PUBLIC ${SYSTEM_INSTALL_DEPENDENCIES}
        # PUBLIC Dynamic_Static.Core
        PUBLIC ${Dynamic_Static.Core.LIBRARY}
        PUBLIC ${GLFW.LIBRARY}
        PUBLIC ${SYSTEM_INSTALL_DEPENDENCIES}
    )

    # add_dependencies(${TARGET} Dynamic_Static.Core)
    add_dependencies(${TARGET} Dynamic_Static.Core.package)
    add_dependencies(${TARGET} GLFW)

    export(
        TARGETS ${TARGET}
        FILE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.package.cmake
    )
# endif()
