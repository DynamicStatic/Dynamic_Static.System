
################################################################################
include(CheckCXXCompilerFlag)
function(dst_set_cxx_flag cxxFlag)
    CHECK_CXX_COMPILER_FLAG(cxxFlag CXX_FLAG_AVAILABLE)
    if (CXX_FLAG_AVAILABLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} cxxFlag")
    endif()
endfunction()
################################################################################
function(dst_create_project projectName)
    project(${projectName} CXX)
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
function(dst_create_file_group fileGroup)
    foreach(file ${fileGroup})
        get_filename_component(PARENT_DIR "${file}" DIRECTORY)
        string(REPLACE "${CMAKE_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
        if (MSVC)
            string(REPLACE "/" "\\" GROUP "${GROUP}")
        endif()
        source_group("${GROUP}" FILES "${file}")
    endforeach()
endfunction()
################################################################################
function(dst_create_static_library includeFiles sourceFiles)
    add_library(${CMAKE_PROJECT_NAME} STATIC ${includeFiles} ${sourceFiles})
    set_target_properties(
        ${CMAKE_PROJECT_NAME}
        PROPERTIES
            PREFIX ""
            LINKER_LANGUAGE CXX
            # PUBLIC_HEADER "${includeFiles}"
    )

    dst_create_file_group("${includeFiles}")
    dst_create_file_group("${sourceFiles}")

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
function(dst_create_shared_library includeFiles sourceFiles)
    add_library(${CMAKE_PROJECT_NAME} SHARED ${includeFiles} ${sourceFiles})
    set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)
    set_target_properties(
        ${CMAKE_PROJECT_NAME}
        PROPERTIES
            PREFIX ""
            LINKER_LANGUAGE CXX
            # PUBLIC_HEADER "${includeFiles}"
            # CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE
            # BUILD_SHARED_LIBS TRUE
    )

    dst_create_file_group("${includeFiles}")
    dst_create_file_group("${sourceFiles}")

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
macro(dst_list_include_directories)
    get_property(
        includeDirectories
        TARGET ${CMAKE_PROJECT_NAME}
        PROPERTY INCLUDE_DIRECTORIES
    )

    message("${CMAKE_PROJECT_NAME} include directories")
    foreach(includeDirectory ${includeDirectories})
        message("    ${includeDirectory}")
    endforeach()
endmacro()
################################################################################
macro(dst_install_library includeDirectories)
    set(packageDirectory "${PROJECT_SOURCE_DIR}/../packages/${CMAKE_PROJECT_NAME}/")
    foreach(includeDirectory ${includeDirectories})
        install(
            DIRECTORY "${includeDirectory}"
            DESTINATION "${packageDirectory}/include/"
        )
    endforeach()

    get_property(
        addtionalIncludeDirectories
        TARGET ${CMAKE_PROJECT_NAME}
        PROPERTY INCLUDE_DIRECTORIES
    )

    foreach(additionalIncludeDirectory ${addtionalIncludeDirectories})
        install(
            DIRECTORY "${additionalIncludeDirectory}"
            DESTINATION "${packageDirectory}/include/"
        )
    endforeach()

    install(
        TARGETS ${CMAKE_PROJECT_NAME}
        ARCHIVE DESTINATION "${packageDirectory}/lib/"
        LIBRARY DESTINATION "${packageDirectory}/bin/"
        RUNTIME DESTINATION "${packageDirectory}/bin/"
    )
endmacro()
################################################################################
