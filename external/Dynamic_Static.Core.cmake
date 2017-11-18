
include(ExternalProject)
ExternalProject_Add(
    Dynamic_Static.Core.package
    PREFIX external
    DOWNLOAD_DIR external/Dynamic_Static.Core
    URL https://github.com/DynamicStatic/Dynamic_Static.Core/archive/master.zip
    CMAKE_ARGS
        -DBUILD_SANDBOX=OFF
        -DBUILD_TESTS=OFF
    INSTALL_COMMAND ""
)

set(Dynamic_Static.Core.ready FALSE)
ExternalProject_Get_Property(Dynamic_Static.Core.package BINARY_DIR)
set(Dynamic_Static.Core.configuration ${BINARY_DIR}/Dynamic_Static.Core.package.cmake)
if (EXISTS ${Dynamic_Static.Core.configuration})
    include(${Dynamic_Static.Core.configuration})
    get_target_property(
        Dynamic_Static.Core.includeDirectories
        Dynamic_Static.Core
        INTERFACE_INCLUDE_DIRECTORIES
    )

    set(Dynamic_Static.Core.ready TRUE)
endif()
