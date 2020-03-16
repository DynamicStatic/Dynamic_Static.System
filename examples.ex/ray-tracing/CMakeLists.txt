
# ==========================================
#   Copyright (c) 2020 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

set(includeDirectory "${CMAKE_CURRENT_LIST_DIR}/include/")
set(sourceDirectory "${CMAKE_CURRENT_LIST_DIR}/source/")
DstAddExecutable(
    target ray-tracing
    folder Dynamic_Static.System/examples/
    linkLibraries Dynamic_Static.System
    includeDirectories "${includeDirectory}"
    includeFiles
        "${includeDirectory}/defines.hpp"
    sourceFiles
        "${sourceDirectory}/main.cpp"
)
