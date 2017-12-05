
dst_add_external_project_ex(
    target glfw
    URL https://github.com/glfw/glfw/archive/3.2.1.zip
    URL_HASH SHA1=3578BEFA2B96A6A2286F33C3A92E08E9F2F834F8
    CMAKE_ARGS
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
)

set(glfw.includeDirectories "${glfw.sourceDirectory}/include/")
if (MSVC)
    set(glfw.linkLibraries
        "${glfw.buildDirectory}/$(Configuration)/glfw3.lib"
        glu32.lib
        opengl32.lib
    )
else()
    set(glfw.linkLibraries
        "${glfw.buildDirectory}/libglfw3.a"
        EGL
        GL
        X11
        Xcursor
        Xi
        Xinerama
        Xrandr
        Xxf86vm
    )
endif()

# TODO : Confirm this on all platforms...
# set(glfw.linkLibraries
#     $<$<PLATFORM_ID:Windows>:
#         "${glfw.buildDirectory}/$(Configuration)/glfw3.lib"
#         glu32.lib
#         opengl32.lib
#     >
#     $<$<PLATFORM_ID:Linux>:
#         "${glfw.buildDirectory}/libglfw3.a"
#         EGL
#         GL
#         X11
#         Xcursor
#         Xi
#         Xinerama
#         Xrandr
#         Xxf86vm
#     >
# )
