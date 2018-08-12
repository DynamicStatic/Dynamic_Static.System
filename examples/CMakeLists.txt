
# ==========================================
#   Copyright (c) 2018-2018 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

macro(CreateExample target)
    DstCreateExecutable(
        target ${target}
        folder Dynamic_Static.System/examples/

        sharedLibraries
            ${FMOD.sharedLibraries}
            ${glew.sharedLibraries}

        staticLibraries
            Dynamic_Static.System

        sourceFiles
            "${CMAKE_CURRENT_LIST_DIR}/${target}.cpp"
    )
endmacro()

CreateExample(BasicAudio)
CreateExample(BasicGui)
CreateExample(GLGears)
