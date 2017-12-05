
dst_add_external_project_ex(
    target Dynamic_Static.Core
    URL https://github.com/DynamicStatic/Dynamic_Static.Core/archive/refactor/build-system.zip
    CMAKE_ARGS -DBUILD_TESTS=OFF
)

include("${Dynamic_Static.Core.buildDirectory}/Dynamic_Static.Core.package.cmake")

get_target_property(
    Dynamic_Static.Core.includeDirectories
    Dynamic_Static.Core
    INTERFACE_INCLUDE_DIRECTORIES
)

get_target_property(
    Dynamic_Static.Core.linkLibraries
    Dynamic_Static.Core
    INTERFACE_LINK_LIBRARIES
)

if ("${Dynamic_Static.Core.linkLibraries}" STREQUAL "Dynamic_Static.Core.linkLibraries-NOTFOUND")
    set(Dynamic_Static.Core.linkLibraries "")
endif()

if (MSVC)
    set(Dynamic_Static.Core.importedLocation
        "${Dynamic_Static.Core.buildDirectory}/$(Configuration)/Dynamic_Static.Core.lib"
    )
else()
    # TODO : Make this work generically for all build configurations...
    get_target_property(
        Dynamic_Static.Core.importedLocation
        Dynamic_Static.Core
        IMPORTED_LOCATION_NOCONFIG
    )
endif()

set(Dynamic_Static.Core.linkLibraries
    "${Dynamic_Static.Core.linkLibraries}"
    "${Dynamic_Static.Core.importedLocation}"
)
