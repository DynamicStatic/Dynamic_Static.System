
# ==========================================
#   Copyright (c) 2016-2020 Dynamic_Static
#     Patrick Purcell
#       Licensed under the MIT license
#     http://opensource.org/licenses/MIT
# ==========================================

if(MSVC)
    set(glew_includeDirectories "${externalDirectory}/glew-2.1.0/include/")
    set(glew_sourceFiles "${externalDirectory}/glew-2.1.0/src/glew.c")
    set_source_files_properties("${glew_sourceFiles}" PROPERTIES COMPILE_FLAGS /w)
    set(glew_compileDefinitions "GLEW_STATIC")
endif()
