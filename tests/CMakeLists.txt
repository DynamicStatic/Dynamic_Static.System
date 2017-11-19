
set(sourcePath "${PROJECT_SOURCE_DIR}/tests/source/")
set(sourceFiles
    ${sourcePath}/Main.cpp
)

set(catch.include "${CMAKE_BINARY_DIR}/tests/external/catch/")
file(
    DOWNLOAD
    https://github.com/catchorg/Catch2/releases/download/v2.0.1/catch.hpp
    ${catch.include}/catch.hpp
)

set(TARGET Dynamic_Static.System.Tests)
add_executable(${TARGET} "${sourceFiles}")
add_dependencies(${TARGET} Dynamic_Static.System)
dst_setup_target(${TARGET} "" "${sourceFiles}")
target_include_directories(${TARGET} PUBLIC ${catch.include})
target_link_libraries(${TARGET} Dynamic_Static.System)
