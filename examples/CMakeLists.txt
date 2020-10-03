
# ==========================================
#   Copyright (c) 2018-2020 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

macro(dst_add_example target)
    dst_add_executable(
        target ${target}
        folder dynamic_static.system/examples/
        linkLibraries dynamic_static.system
        sourceFiles "${CMAKE_CURRENT_LIST_DIR}/${target}.cpp"
    )
endmacro()
dst_add_example(gears-with-gui)
dst_add_example(gl-gears)
dst_add_example(im-gui)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ray-tracing/")
