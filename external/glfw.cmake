
include(ExternalProject)
ExternalProject_Add(
    glfw
    PREFIX external
    DOWNLOAD_DIR external/glfw
    URL https://github.com/glfw/glfw/archive/3.2.1.zip
    URL_HASH SHA1=3578BEFA2B96A6A2286F33C3A92E08E9F2F834F8
    CMAKE_ARGS
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(glfw SOURCE_DIR)
ExternalProject_Get_Property(glfw BINARY_DIR)
set(glfw.include "${SOURCE_DIR}/include/")
if (MSVC)
    set(glfw.library "${BINARY_DIR}/src/$(Configuration)/glfw3.lib")
else()
    set(glfw.library "${BINARY_DIR}/src/libglfw3.a")
endif()
