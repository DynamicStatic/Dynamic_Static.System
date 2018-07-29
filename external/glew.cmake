
# ==========================================
#   Copyright (c) 2016-2018 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

if(MSVC)
    set(glew.includeDirectories "${PROJECT_SOURCE_DIR}/external/glew-2.1.0/include/")
    set(glew.staticLibraries "${PROJECT_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64/glew32.lib")
    set(glew.sharedLibraries "${PROJECT_SOURCE_DIR}/external/glew-2.1.0/bin/Release/x64/glew32.dll")
else()
    set(glew.includeDirectories "")
    set(glew.staticLibraries "")
    set(glew.sharedLibraries "")
endif()
