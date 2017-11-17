
################################################################################
include(CheckCXXCompilerFlag)
function(dst_set_cxx_flag CXX_FLAG)
    CHECK_CXX_COMPILER_FLAG(CXX_FLAG CXX_FLAG_AVAILABLE)
    if (CXX_FLAG_AVAILABLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} CXX_FLAG")
    endif()
endfunction()
################################################################################
function(dst_create_project PROJECT_NAME)
    project(${PROJECT_NAME} CXX)
    set(CMAKE_CXX_STANDARD 14)
    dst_set_cxx_flag(-W4)
    dst_set_cxx_flag(-Wall)
    dst_set_cxx_flag(-Wextra)
    dst_set_cxx_flag(-Wuninitialized)
    dst_set_cxx_flag(-Wwrite-strings)
    dst_set_cxx_flag(-Wpointer-arith)
    dst_set_cxx_flag(-Wunreachable-code)
    dst_set_cxx_flag(-Wstrict_prototypes)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    add_definitions(-DUNICODE -D_UNICODE)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endfunction()
################################################################################
function(dst_create_file_group FILE_GROUP)
    foreach(FILE ${FILE_GROUP})
        get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
        string(REPLACE "${CMAKE_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
        if (MSVC)
            string(REPLACE "/" "\\" GROUP "${GROUP}")
        endif()
        source_group("${GROUP}" FILES "${FILE}")
    endforeach()
endfunction()
################################################################################
function(dst_create_static_library INCLUDE_FILES SOURCE_FILES)
    include(CPack)
    add_library(${CMAKE_PROJECT_NAME} STATIC ${INCLUDE_FILES} ${SOURCE_FILES})
    set_target_properties(
        ${CMAKE_PROJECT_NAME}
        PROPERTIES
            PREFIX ""
            LINKER_LANGUAGE CXX
            # PUBLIC_HEADER "${INCLUDE_FILES}"
    )

    dst_create_file_group("${INCLUDE_FILES}")
    dst_create_file_group("${SOURCE_FILES}")

    target_include_directories(
        ${CMAKE_PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include/
    )

    if (NOT MSVC)
        target_link_libraries(
            ${CMAKE_PROJECT_NAME}
            PUBLIC dl
            PUBLIC pthread
            PUBLIC stdc++fs
        )
    endif()

    export(
        TARGETS ${CMAKE_PROJECT_NAME}
        FILE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.package.cmake
    )
endfunction()
################################################################################
function(dst_create_shared_library INCLUDE_FILES SOURCE_FILES)
    add_library(${CMAKE_PROJECT_NAME} SHARED ${INCLUDE_FILES} ${SOURCE_FILES})
    set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)
    set_target_properties(
        ${CMAKE_PROJECT_NAME}
        PROPERTIES
            PREFIX ""
            LINKER_LANGUAGE CXX
            # PUBLIC_HEADER "${INCLUDE_FILES}"
            # CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE
            # BUILD_SHARED_LIBS TRUE
    )

    dst_create_file_group("${INCLUDE_FILES}")
    dst_create_file_group("${SOURCE_FILES}")

    target_include_directories(
        ${CMAKE_PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include/
    )

    if (NOT MSVC)
        target_link_libraries(
            ${CMAKE_PROJECT_NAME}
            PUBLIC dl
            PUBLIC pthread
            PUBLIC stdc++fs
        )
    endif()

    # include(GenerateExportHeader)
    # generate_export_header(${CMAKE_PROJECT_NAME})
    export(
        TARGETS ${CMAKE_PROJECT_NAME}
        FILE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.package.cmake
    )
endfunction()
################################################################################
macro(dst_install_library)
    get_property(
        ADDITIONAL_INCLUDE_DIRECTORIES
        TARGET ${CMAKE_PROJECT_NAME}
        PROPERTY INCLUDE_DIRECTORIES
    )

    foreach(additionalIncludeDirectory ${ADDITIONAL_INCLUDE_DIRECTORIES})
        install(
            DIRECTORY "${additionalIncludeDirectory}"
            DESTINATION "${PROJECT_SOURCE_DIR}/../package/${CMAKE_PROJECT_NAME}/include/"
        )
    endforeach()

    if (MSVC)
        install(
            TARGETS ${CMAKE_PROJECT_NAME}
            RUNTIME DESTINATION "${PROJECT_SOURCE_DIR}/../package/${CMAKE_PROJECT_NAME}/bin/"
        )
    else()
        install(
            TARGETS ${CMAKE_PROJECT_NAME}
            LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/../package/${CMAKE_PROJECT_NAME}/bin/"
        )
    endif()
endmacro()
################################################################################
