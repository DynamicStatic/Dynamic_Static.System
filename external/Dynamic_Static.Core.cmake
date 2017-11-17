
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

# # NOTE : We're setting up the INCLUDE and LIBRARY variables for dst::core because without the INCLUDE
# #        it won't get added to the build target's INCLUDE_DIRECTORIES property...super annoying.
# # NOTE : There's a comment with some more detail in source/CMakeLists.txt.
# ExternalProject_Get_Property(Dynamic_Static.Core.package BINARY_DIR)
# set(Dynamic_Static.Core.PACKAGE ${BINARY_DIR}/Dynamic_Static.Core.package.cmake)
# if (EXISTS ${Dynamic_Static.Core.PACKAGE})
#     include(${Dynamic_Static.Core.PACKAGE})
# endif()

ExternalProject_Get_Property(Dynamic_Static.Core.package SOURCE_DIR)
ExternalProject_Get_Property(Dynamic_Static.Core.package BINARY_DIR)
set(Dynamic_Static.Core.INCLUDE "${SOURCE_DIR}/include/")
if (MSVC)
    set(Dynamic_Static.Core.LIBRARY "${BINARY_DIR}/source/$(Configuration)/Dynamic_Static.Core.lib")
else()
    set(Dynamic_Static.Core.LIBRARY "${BINARY_DIR}/source/Dynamic_Static.Core.a")
endif()
