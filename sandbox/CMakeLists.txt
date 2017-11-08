
# CMake configuration for Dynamic_Static.System.Sandbox

set(INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(INCLUDE_FILES
)

set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/)
set(SOURCE_FILES
    ${SOURCE_DIRECTORY}/Main.cpp
)

create_file_group("${INCLUDE_FILES}")
create_file_group("${SOURCE_FILES}")

set(TARGET Dynamic_Static.System.Sandbox)
add_executable(${TARGET} ${INCLUDE_FILES} ${SOURCE_FILES})
target_include_directories(${TARGET} PUBLIC ${INCLUDE_DIRECTORY})
target_link_libraries(${TARGET} Dynamic_Static.System)
