
set(target GLGears)
set(includePath "${PROJECT_SOURCE_DIR}/examples/${target}/include/")
set(includeFiles
)

set(sourcePath "${PROJECT_SOURCE_DIR}/examples/${target}/source/")
set(sourceFiles
    ${sourcePath}/Main.cpp
)

add_executable(${target} "${sourceFiles}")
dst_setup_target(${target} "" "${sourceFiles}")
target_link_libraries(${target} Dynamic_Static.System)
set_target_properties(${target} PROPERTIES FOLDER Examples)
add_dependencies(${target} Dynamic_Static.System)
