
# ==========================================
#   Copyright (c) 2016-2018 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

if(MSVC)
    set(glew.includeDirectories "${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/include/")
    set(glew.sourceFiles "${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/src/glew.c")
endif()
