
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
    folder dynamic_static.system/examples/
    linkLibraries dynamic_static.system
    includeDirectories "${includeDirectory}"
    includeFiles
        "${includeDirectory}/camera.hpp"
        "${includeDirectory}/defines.hpp"
        "${includeDirectory}/hitable.hpp"
        "${includeDirectory}/ray.hpp"
        "${includeDirectory}/ray-tracer.hpp"
        "${includeDirectory}/sphere.hpp"
    sourceFiles
        "${sourceDirectory}/main.cpp"
)
