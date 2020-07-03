
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
        "${includeDirectory}/materials/dialectric.hpp"
        "${includeDirectory}/materials/lambert.hpp"
        "${includeDirectory}/materials/material.hpp"
        "${includeDirectory}/materials/metal.hpp"
        "${includeDirectory}/camera.hpp"
        "${includeDirectory}/defines.hpp"
        "${includeDirectory}/hittable.hpp"
        "${includeDirectory}/rasterizer.hpp"
        "${includeDirectory}/ray.hpp"
        "${includeDirectory}/ray-tracer.hpp"
        "${includeDirectory}/renderer.hpp"
        "${includeDirectory}/scene.hpp"
        "${includeDirectory}/sphere.hpp"
        "${includeDirectory}/sphere-vertices.hpp"
        "${includeDirectory}/sphere-indices.hpp"
        "${includeDirectory}/utilities.hpp"
    sourceFiles
        "${sourceDirectory}/hittable.cpp"
        "${sourceDirectory}/main.cpp"
)
