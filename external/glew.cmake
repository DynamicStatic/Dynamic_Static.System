
# ==========================================
#   Copyright (c) 2016-2020 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

if(MSVC)
    set(glew_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/")
    set(glewIncludeDirectory "${glew_SOURCE_DIR}/include/")
    set(glewSourceDirectory "${glew_SOURCE_DIR}/src/")
    add_library(
        glew STATIC
        "${glewIncludeDirectory}/GL/eglew.h"
        "${glewIncludeDirectory}/GL/glew.h"
        "${glewIncludeDirectory}/GL/glxew.h"
        "${glewIncludeDirectory}/GL/wglew.h"
        "${glewSourceDirectory}/glew.c"
        "${glewSourceDirectory}/glewinfo.c"
        "${glewSourceDirectory}/visualinfo.c"
    )
    target_include_directories(glew PUBLIC "${glewIncludeDirectory}")
    target_compile_definitions(glew PUBLIC GLEW_STATIC)
    set_target_properties(glew PROPERTIES FOLDER "external/")
    set_target_properties(glew PROPERTIES LINKER_LANGUAGE CXX)
    # target_compile_options(glew PRIVATE /w)
    target_compile_features(glew PUBLIC cxx_std_17)
endif()
