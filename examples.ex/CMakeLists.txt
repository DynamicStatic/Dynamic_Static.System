
#==========================================
#    Copyright 2011-2018 Dynamic_Static
#        Patrick Purcell
#    Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

macro(CreateExample target)
    DstCreateExecutable(
        target ${target}
        folder Dynamic_Static.System/examples/
        staticLibraries Dynamic_Static.System
        sourceFiles "${CMAKE_CURRENT_LIST_DIR}/${target}.cpp"
        sharedLibraries
            ${FMOD.sharedLibraries}
            ${glew.sharedLibraries}
    )
endmacro()

CreateExample(GLGears)
