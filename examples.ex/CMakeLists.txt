
# ==========================================
#   Copyright (c) 2018-2020 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

macro(AddExample target)
    DstAddExecutable(
        target ${target}
        folder Dynamic_Static.System/examples/
        linkLibraries Dynamic_Static.System
        sourceFiles "${CMAKE_CURRENT_LIST_DIR}/${target}.cpp"
    )
endmacro()
AddExample(gears-with-gui)
AddExample(gl-gears)
AddExample(im-gui)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ray-tracing/")
