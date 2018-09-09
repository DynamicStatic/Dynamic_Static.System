
# ==========================================
#   Copyright (c) 2018-2018 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

macro(CreateExample target)
    list(APPEND external.sharedLibraries)
    if(BUILD_DST_SYS_AUDIO)
        list(APPEND external.sharedLibraries "${FMOD.sharedLibraries}")
    endif()
    DstCreateExecutable(
        target ${target}
        folder Dynamic_Static.System/examples/
        sharedLibraries "${external.sharedLibraries}"
        staticLibraries Dynamic_Static.System
        sourceFiles "${CMAKE_CURRENT_LIST_DIR}/${target}.cpp"
    )
endmacro()

if(BUILD_DST_SYS_AUDIO)
    CreateExample(BasicAudio)
endif()
CreateExample(BasicGui)
CreateExample(GLGears)
