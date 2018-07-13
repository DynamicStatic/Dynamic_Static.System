
# ==========================================
#   Copyright (c) 2016-2018 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

if(MSVC)
    set(glew.includeDirectory "${PROJECT_SOURCE_DIR}/external/glew-2.1.0/include/")
    set(glew.staticLinkLibraries "${PROJECT_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64/glew32s.lib")
else()
    set(glew.includeDirectory "")
    set(glew.linkLibraries "")
endif()
