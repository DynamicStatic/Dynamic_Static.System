
macro(add_example target)
    dst_add_executable(
        target ${target}
        folder examples
        buildDependencies Dynamic_Static.System
        linkLibraries Dynamic_Static.System
        sourceFiles "${CMAKE_CURRENT_SOURCE_DIR}/${target}.cpp"
    )
endmacro()

add_example(GLGears)

if(BUILD_AUDIO_SUPPORT)
    add_example(OggVorbis)
endif()
